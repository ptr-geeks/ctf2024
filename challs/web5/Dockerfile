FROM python:3.12-slim

ENV FLAG="ptr{fake_flag}"

WORKDIR /app
RUN apt-get update && \
		apt-get install -y curl && \
		pip install --no-cache-dir flask

COPY chall /app

CMD ["python", "app.py"]
