# User documentation

## What this stack provides

| Service | What it does | Reachable from outside? |
|---------|--------------|-------------------------|
| **nginx** | HTTPS web server, the only entrypoint (port 443, TLSv1.2/1.3) | Yes, `https://mamuzamm.42.fr` |
| **wordpress** | The WordPress website, executed by php-fpm | No, only through nginx |
| **mariadb** | The database that stores posts, users and settings | No |

## Start and stop

Run these commands from the root of the repository:

```sh
make          # build (first time) and start everything
make stop     # stop the containers, keep them
make start    # start the stopped containers again
make down     # stop and remove the containers (website data is kept)
```

## Access the website

1. Make sure the domain points to this machine (only needed once):
   ```sh
   grep mamuzamm.42.fr /etc/hosts || echo "127.0.0.1 mamuzamm.42.fr" | sudo tee -a /etc/hosts
   ```
2. Website: **https://mamuzamm.42.fr**
3. Administration panel: **https://mamuzamm.42.fr/wp-admin**

The certificate is self-signed, so the browser shows a warning the first time.
Click *Advanced* → *Accept the risk / Proceed*.

`http://mamuzamm.42.fr` (port 80) does not work, on purpose: only HTTPS on
port 443 is allowed.

## Credentials

| What | Where |
|------|-------|
| WordPress administrator name | `WP_ADMIN_USER` in `srcs/.env` |
| WordPress second user (author) | `WP_USER` in `srcs/.env` |
| Their passwords | `secrets/credentials.txt` |
| Database user name | `MYSQL_USER` in `srcs/.env` |
| Database user password | `secrets/db_password.txt` |
| Database root password | `secrets/db_root_password.txt` |

```sh
cat secrets/credentials.txt
```

These files are created automatically by `make` the first time, with random
passwords. They are **not** in git and must never be committed.

To use your own passwords, edit the files **before the first `make`**.
After the first start, the passwords are stored in the database. If you
change the files later, you must reset everything with `make fclean && make`
(this erases the website data).

## Check that everything works

```sh
make ps
```
All three containers should be `Up`, and `mariadb` should show `(healthy)`.

```sh
make logs                      # follow all logs (Ctrl+C to quit)
docker logs wordpress          # logs of one service
```

Quick checks:

```sh
curl -k https://mamuzamm.42.fr          # returns the WordPress HTML page
curl http://mamuzamm.42.fr              # fails: port 80 is closed
docker exec -it mariadb mariadb -u root # fails: root needs a password
```
