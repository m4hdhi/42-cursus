#!/bin/sh
# Install and configure WordPress on first start, then replace this script with php-fpm (PID 1).
set -e

DB_PASSWORD=$(cat /run/secrets/db_password)
# Sets WP_ADMIN_PASSWORD and WP_USER_PASSWORD
. /run/secrets/credentials

cd /var/www/html

if [ ! -f wp-load.php ]; then
    wp core download --allow-root
fi

if [ ! -f wp-config.php ]; then
    wp config create --allow-root \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${DB_PASSWORD}" \
        --dbhost=mariadb:3306 \
        --skip-check
fi

if ! wp core is-installed --allow-root 2> /dev/null; then
    wp core install --allow-root \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --skip-email
    wp user create --allow-root "${WP_USER}" "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="${WP_USER_PASSWORD}"
    # Publish comments right away (by default, a user's first comment
    # waits for an admin to approve it)
    wp option update --allow-root comment_previously_approved 0
fi

chown -R www-data:www-data /var/www/html

# -F: stay in the foreground
exec php-fpm8.2 -F
