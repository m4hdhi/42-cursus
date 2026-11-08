FROM debian:bookworm

RUN apt-get update && apt-get install -y --no-install-recommends nginx openssl \
    && rm -rf /var/lib/apt/lists/*

# Passed by docker-compose.yml from srcs/.env
ARG DOMAIN_NAME

# Self-signed TLS certificate for our domain
RUN mkdir -p /etc/nginx/ssl \
    && openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/nginx/ssl/inception.key \
        -out /etc/nginx/ssl/inception.crt \
        -subj "/C=AE/L=Abu Dhabi/O=42/CN=${DOMAIN_NAME}"

# Replace the default site (port 80) with ours (port 443 only)
COPY conf/nginx.conf /etc/nginx/conf.d/inception.conf
RUN rm -f /etc/nginx/sites-enabled/default /var/www/html/index.nginx-debian.html \
    && sed -i "s/DOMAIN_NAME/${DOMAIN_NAME}/" /etc/nginx/conf.d/inception.conf

EXPOSE 443

# Run in the foreground so nginx is PID 1 and the container stays alive
CMD ["nginx", "-g", "daemon off;"]
