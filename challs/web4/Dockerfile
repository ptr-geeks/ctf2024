FROM rust:1.80-alpine3.20 AS builder

WORKDIR /app

COPY chall /app

RUN apk add --no-cache musl-dev && \
    cargo build --release


FROM alpine:3.20

ENV API_KEY=fake_api_key
WORKDIR /app

COPY --from=builder /app/target/release/chall /app/chall
COPY chall/database.sqlite3 /app/database.sqlite3
COPY chall/static /app/static
COPY chall/data /app/data

CMD ["/app/chall"]
