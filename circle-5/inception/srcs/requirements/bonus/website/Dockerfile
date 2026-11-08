FROM debian:bookworm

RUN apt-get update && apt-get install -y --no-install-recommends nginx \
    && rm -rf /var/lib/apt/lists/*

# Serve only our static site, on port 8080 (internal to the Docker network)
COPY conf/website.conf /etc/nginx/conf.d/website.conf
RUN rm -f /etc/nginx/sites-enabled/default

COPY site/ /var/www/website/

EXPOSE 8080

CMD ["nginx", "-g", "daemon off;"]
