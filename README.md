*This project has been created as part of the 42 curriculum by mamuzamm.*

# Inception

## Description

Inception is a system administration project. The goal is to build a small web
infrastructure with **Docker Compose**, inside a virtual machine, where every
service runs in its own container built from my own Dockerfile.

The stack serves a WordPress website at `https://mamuzamm.42.fr`:

```
            host:443 (HTTPS, TLSv1.2/1.3 only)
                     │
            ┌────────▼────────┐
            │      nginx      │  reverse proxy + TLS
            └────────┬────────┘
                     │ FastCGI (port 9000)
            ┌────────▼────────┐
            │    wordpress    │  WordPress + php-fpm
            └────────┬────────┘
                     │ MySQL protocol (port 3306)
            ┌────────▼────────┐
            │     mariadb     │  database
            └─────────────────┘
   all three containers are on the "inception" bridge network
```

- **nginx** is the only entrypoint: it is the only container with a published
  port (443). It serves static files and forwards `.php` requests to php-fpm.
- **wordpress** runs php-fpm, which executes the WordPress PHP code. It is not
  reachable from outside.
- **mariadb** stores the WordPress database. It is not reachable from outside.
- Two **named volumes** keep the data on the host in `/home/mamuzamm/data`:
  `mariadb` (database files) and `wordpress` (website files).

### Use of Docker and sources included

Each service has its own folder in `srcs/requirements/` with a `Dockerfile`, a
`conf/` folder (configuration files copied into the image) and, if needed, a
`tools/` folder (the startup script).

| File | Role |
|------|------|
| `Makefile` | Creates the data folders, `.env` and secrets, then runs `docker compose` |
| `srcs/docker-compose.yml` | Describes the 3 services, the 2 volumes, the network and the secrets |
| `srcs/.env.example` | Template for `srcs/.env` (domain, database name, user names) |
| `mariadb/conf/50-server.cnf` | MariaDB config: listen on `0.0.0.0:3306` so WordPress can connect |
| `mariadb/tools/init.sh` | First start: creates the database, the user and the root password. Then starts `mariadbd` |
| `nginx/conf/nginx.conf` | HTTPS server on port 443, TLSv1.2/1.3, forwards PHP to `wordpress:9000` |
| `wordpress/conf/www.conf` | php-fpm pool: listen on port 9000 instead of a Unix socket |
| `wordpress/tools/setup.sh` | First start: downloads, configures and installs WordPress with WP-CLI, creates the 2 users. Then starts `php-fpm` |

### Main design choices

- **Base image: `debian:bookworm` (Debian 12).** It is the penultimate stable
  Debian release (the current one is Debian 13 "trixie"). Debian is well
  documented and its package names are easy to read.
- **One process per container, running as PID 1.** The startup scripts end
  with `exec`, which replaces the shell with the real service (`mariadbd`,
  `php-fpm8.2 -F`, `nginx -g 'daemon off;'`). The service then receives the
  stop signals from Docker directly. There is no `tail -f`, `sleep` or infinite loop.
- **Idempotent startup scripts.** They only initialize what does not exist yet,
  so restarting a container never reinstalls or erases data.
- **Startup order with a healthcheck.** `wordpress` waits until `mariadb` is
  *healthy* (it answers `mariadb-admin ping`), so no waiting loop is needed in
  the scripts.
- **Passwords only in Docker secrets.** `srcs/.env` holds non-sensitive settings.
  Passwords are in `secrets/*.txt`, which the Makefile generates randomly the
  first time. Both are ignored by git.
- **Self-signed TLS certificate** generated with `openssl` at image build time,
  for the domain given in `.env`.
- **Images are tagged `<service>:inception`**, so their name matches the
  service and they never use the `latest` tag.
- **Restart policy `always`**, so a container that crashes is restarted.

### Virtual Machines vs Docker

A **virtual machine** emulates a full computer: it runs its own kernel on top
of a hypervisor, needs its own OS installation, uses gigabytes of disk and
takes time to boot. **Docker containers** share the host kernel. They are
isolated processes (namespaces, cgroups) with their own filesystem, so they
start in seconds and only contain the application and its libraries. VMs give
stronger isolation, while containers are lighter, faster and easier to
reproduce. In this project we use both: the VM is the host, and Docker isolates
each service inside it.

### Secrets vs Environment Variables

**Environment variables** are easy to use, but they are visible in
`docker inspect`, to every process in the container, and often end up in logs
or in git. **Docker secrets** are files mounted read-only in
`/run/secrets/<name>` only in the containers that declare them. They don't
appear in `docker inspect` or in the environment. Here, `.env` holds
configuration (domain, user names, database name) and secrets hold the
passwords.

### Docker Network vs Host Network

With **`network: host`** a container uses the host network stack directly:
there is no isolation, and every port the service opens is open on the host.
A **user-defined bridge network** (`inception`) creates a private network for
our containers. They can reach each other by service name (Docker's internal
DNS resolves `mariadb` and `wordpress`). Only the ports we explicitly publish
(`443`) are reachable from outside. That is why MariaDB and php-fpm are not
exposed.

### Docker Volumes vs Bind Mounts

A **bind mount** maps any host path into a container. It depends on the host
folder structure and is not managed by Docker. A **named volume** is created
and managed by Docker (`docker volume ls/inspect/rm`), has a name, and is
declared in the compose file. Here we use named volumes with the `local`
driver and the options `type: none, o: bind, device: /home/mamuzamm/data/...`.
They stay real Docker volumes, managed by Docker, but their data is stored in
the folder required by the subject.

## Instructions

Requirements: a Linux VM with Docker Engine, the Docker Compose plugin, `make`
and `openssl`.

1. Point the domain to the VM itself:
   ```sh
   echo "127.0.0.1 mamuzamm.42.fr" | sudo tee -a /etc/hosts
   ```
2. Build and start everything:
   ```sh
   make
   ```
   The first run creates `/home/mamuzamm/data/{mariadb,wordpress}`, `srcs/.env`
   and random passwords in `secrets/`.
3. Open `https://mamuzamm.42.fr` (accept the self-signed certificate warning).
   The admin panel is at `https://mamuzamm.42.fr/wp-admin`. The passwords are
   in `secrets/credentials.txt`.

| Command | Effect |
|---------|--------|
| `make` / `make up` | Build images and start the stack |
| `make down` | Stop and remove the containers (data kept) |
| `make stop` / `make start` | Pause / resume the containers |
| `make ps` / `make logs` | Show status / follow logs |
| `make clean` | `down` + remove the images |
| `make fclean` | `clean` + remove volumes and all data in `/home/mamuzamm/data` |
| `make re` | `fclean` then `make` |

See [USER_DOC.md](USER_DOC.md) and [DEV_DOC.md](DEV_DOC.md) for more details.

## Resources

- Dockerfile reference: https://docs.docker.com/reference/dockerfile/
- Dockerfile best practices: https://docs.docker.com/build/building/best-practices/
- Compose file reference: https://docs.docker.com/reference/compose-file/
- Secrets in Compose: https://docs.docker.com/compose/how-tos/use-secrets/
- Volumes: https://docs.docker.com/engine/storage/volumes/
- Bind mounts: https://docs.docker.com/engine/storage/bind-mounts/
- Bridge network: https://docs.docker.com/engine/network/drivers/bridge/
- Host network: https://docs.docker.com/engine/network/drivers/host/
- NGINX SSL module: https://nginx.org/en/docs/http/ngx_http_ssl_module.html
- NGINX FastCGI module: https://nginx.org/en/docs/http/ngx_http_fastcgi_module.html
- php-fpm configuration: https://www.php.net/manual/en/install.fpm.configuration.php
- mariadb-install-db: https://mariadb.com/kb/en/mariadb-install-db/
- WP-CLI commands: https://developer.wordpress.org/cli/commands/
- Debian releases: https://www.debian.org/releases/

### Use of AI

AI (Claude, by Anthropic) was used to:

- draft the first version of the Dockerfiles, startup scripts, `docker-compose.yml`,
  `Makefile` and the documentation files;
- write and run test commands (TLS version checks, crash/restart test,
  persistence test, database access checks);
- explain concepts (PID 1 and `exec`, MariaDB bootstrap mode, named volumes
  with bind options, Docker secrets).

I reviewed, tested and modified all generated content, and I can explain every line.
