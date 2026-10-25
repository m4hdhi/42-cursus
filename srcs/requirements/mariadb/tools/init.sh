#!/bin/sh
# Prepare MariaDB on first start, then replace this script with the server (PID 1).
set -e

DB_PASSWORD=$(cat /run/secrets/db_password)
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)

# The data dir is a volume coming from the host: make sure mysql owns it
mkdir -p /run/mysqld
chown -R mysql:mysql /var/lib/mysql /run/mysqld

# Empty volume: create the system tables
if [ ! -d /var/lib/mysql/mysql ]; then
    mariadb-install-db --user=mysql --datadir=/var/lib/mysql --skip-test-db > /dev/null
fi

# Our database does not exist yet: create it, its user, and the root password.
# --bootstrap runs the SQL without starting the network, then exits.
if [ ! -d "/var/lib/mysql/${MYSQL_DATABASE}" ]; then
    mariadbd --user=mysql --bootstrap << EOF
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF
fi

exec mariadbd --user=mysql
