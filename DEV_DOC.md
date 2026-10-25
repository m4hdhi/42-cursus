# Developer documentation

## Set up the environment from scratch

### Prerequisites

- A Linux virtual machine (e.g. Debian) with a user named `mamuzamm`
- Docker Engine and the Docker Compose plugin (`docker compose version`)
- `make`, `openssl`, `git`
- Your user can run Docker (`sudo usermod -aG docker $USER`, then log in again)

### Configuration files

| File | In git? | Content |
|------|---------|---------|
| `srcs/.env.example` | yes | Template: domain, database name, user names, emails |
| `srcs/.env` | **no** | Copy of the template, read by `docker compose` |
| `secrets/db_password.txt` | **no** | Password of the WordPress database user |
| `secrets/db_root_password.txt` | **no** | Password of the MariaDB `root` user |
| `secrets/credentials.txt` | **no** | `WP_ADMIN_PASSWORD=...` and `WP_USER_PASSWORD=...` |

`make` (target `setup`) creates whichever of these files is missing:
`.env` is copied from the template and the secrets get random values
(`openssl rand -hex`). You can also create them by hand before running `make`.

If `secrets/` is missing but `/home/mamuzamm/data` still contains a previous
install (e.g. after a fresh `git clone`), `make` stops with an error instead
of generating new passwords that would not match the existing database.
Either copy the old `secrets/` folder into the clone, or run `make fclean`
to delete the old data and start from scratch.

The administrator name (`WP_ADMIN_USER`) must not contain `admin` or
`administrator`.

### Domain

```sh
echo "127.0.0.1 mamuzamm.42.fr" | sudo tee -a /etc/hosts
```

## Build and launch

```sh
make
```

This runs `setup` and then:

```sh
docker compose -f srcs/docker-compose.yml up -d --build
```

`--build` builds the four images from our Dockerfiles. They are tagged
`nginx:inception`, `wordpress:inception`, `mariadb:inception` and
`website:inception`. Nothing is pulled from Docker Hub except the
`debian:bookworm` base image.

Startup order:

1. `mariadb` starts. On an empty volume, `init.sh` creates the system tables,
   the database, the user and the root password, then runs `mariadbd`.
2. Once its healthcheck passes, `wordpress` starts. On an empty volume,
   `setup.sh` downloads WordPress with WP-CLI, writes `wp-config.php`, installs
   the site and creates the second user. Then it runs `php-fpm8.2 -F`.
3. `website` (bonus) starts at the same time as `mariadb`. It has no
   dependencies and only serves the static files in `bonus/website/site/`.
4. `nginx` starts once `wordpress` and `website` are running, and listens on
   port 443. It forwards `/resume/` to `website:8080`.

To change the resume, edit `srcs/requirements/bonus/website/site/` and run
`make`. The files are copied into the image, so the website image is rebuilt.

## Manage containers and volumes

| Command | Effect |
|---------|--------|
| `make ps` | Status of the containers |
| `make logs` | Follow the logs of all services |
| `make stop` / `make start` | Stop / start without removing |
| `make down` | Remove containers and network (volumes and data kept) |
| `make clean` | `down` + remove images |
| `make fclean` | `clean` + remove volumes and `/home/mamuzamm/data` |
| `make re` | `fclean` + `make` |

Useful Docker commands:

```sh
docker compose -p inception ps                     # status, from any folder
docker exec -it wordpress bash                     # shell in a container
docker exec -it mariadb mariadb -u root -p         # MariaDB console (root password)
docker exec -it mariadb mariadb -u wpuser -p wordpress   # as the WordPress user
                                                   # then: SHOW TABLES; SELECT user_login FROM wp_users;
docker exec wordpress wp user list --allow-root    # WordPress users
docker volume ls                                   # list volumes
docker volume inspect inception_wordpress          # see where the data is
docker network inspect inception                   # see the connected containers
docker compose -f srcs/docker-compose.yml build --no-cache nginx   # rebuild one image
```

## Where the data is stored and how it persists

| Volume | Mounted in | Host folder |
|--------|-----------|-------------|
| `inception_mariadb` | `mariadb:/var/lib/mysql` | `/home/mamuzamm/data/mariadb` |
| `inception_wordpress` | `wordpress:/var/www/html` and `nginx:/var/www/html` | `/home/mamuzamm/data/wordpress` |

They are Docker named volumes (`driver: local`) whose `driver_opts`
(`type: none, o: bind, device: ...`) place the data in `/home/mamuzamm/data`.

- `make down` / `make up`, a container crash or a VM reboot do **not** lose
  data: the startup scripts see that the database and WordPress already exist
  and skip the installation.
- Only `make fclean` deletes the data. The files are owned by the container
  users (`mysql`, `www-data`), so `fclean` deletes them from inside a
  temporary `debian:bookworm` container, where it has root rights.
- If you change a password in `secrets/` after the first start, run
  `make fclean && make`. Otherwise the new password won't match the one stored
  in the database.
