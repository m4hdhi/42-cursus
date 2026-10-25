LOGIN		= mamuzamm
DATA_DIR	= /home/$(LOGIN)/data
COMPOSE		= docker compose -f srcs/docker-compose.yml

all: up

# Create everything the stack needs before it can start:
#   - stop if old data exists without its secrets (fresh clone, old install)
#   - the host folders behind the two named volumes
#   - srcs/.env (copied from the template if missing)
#   - the secret files (random passwords, generated only if missing)
setup:
	@if [ ! -f secrets/db_password.txt ] && [ -f $(DATA_DIR)/wordpress/wp-config.php ]; then \
		echo "Error: $(DATA_DIR) holds a previous install, but secrets/ is missing."; \
		echo "New passwords would not match it. Copy your old secrets/ folder here,"; \
		echo "or run 'make fclean' to delete the old data and start from scratch."; \
		exit 1; \
	fi
	@mkdir -p $(DATA_DIR)/mariadb $(DATA_DIR)/wordpress
	@test -f srcs/.env || cp srcs/.env.example srcs/.env
	@mkdir -p secrets
	@test -f secrets/db_password.txt || openssl rand -hex 16 > secrets/db_password.txt
	@test -f secrets/db_root_password.txt || openssl rand -hex 16 > secrets/db_root_password.txt
	@test -f secrets/credentials.txt || printf "WP_ADMIN_PASSWORD=%s\nWP_USER_PASSWORD=%s\n" \
		$$(openssl rand -hex 12) $$(openssl rand -hex 12) > secrets/credentials.txt
	@chmod 600 secrets/*.txt

up: setup
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

start:
	$(COMPOSE) start

stop:
	$(COMPOSE) stop

ps:
	$(COMPOSE) ps

logs:
	$(COMPOSE) logs -f

# Remove containers, network and images (volumes and data are kept)
clean:
	$(COMPOSE) down --rmi all

# Also remove the volumes and the data on the host.
# The files belong to the container users (mysql, www-data), so we delete
# them from inside a throwaway container, where we are root.
fclean:
	$(COMPOSE) down --rmi all --volumes
	@if [ -d $(DATA_DIR) ]; then \
		docker run --rm -v $(DATA_DIR):/data debian:bookworm \
			sh -c 'rm -rf /data/mariadb /data/wordpress'; \
		rm -rf $(DATA_DIR); \
	fi

re: fclean all

.PHONY: all setup up down start stop ps logs clean fclean re
