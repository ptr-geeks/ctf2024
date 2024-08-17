FROM golang:1.22-alpine AS builder

WORKDIR /app
ENV CGO_ENABLED=1

COPY chall /app

RUN apk add --no-cache gcc musl-dev sqlite-dev
RUN go build -o /app/main


FROM alpine:3.12

WORKDIR /app

COPY --from=builder /app/main /app/main
COPY chall/static /app/static
COPY chall/database.sqlite3 /app

EXPOSE 8080
CMD ["/app/main"]
