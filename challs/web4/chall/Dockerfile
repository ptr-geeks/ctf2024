FROM rust:1.80-alpine3.20 AS builder

WORKDIR /app

COPY . /app

RUN apk add --no-cache musl-dev && \
    cargo build --release


FROM alpine:3.20

ENV API_KEY=fake_api_key
WORKDIR /app

COPY --from=builder /app/target/release/chall /app/chall
COPY database.sqlite3 /app/database.sqlite3
COPY static /app/static
COPY data /app/data

CMD ["/app/chall"]
