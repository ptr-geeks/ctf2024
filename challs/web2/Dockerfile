FROM php:8.3-apache

RUN apt update && \
    apt install -y jq iputils-ping dnsutils

COPY chall/index.php /var/www/html/
COPY flag.txt /flag.txt
