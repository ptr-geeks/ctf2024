FROM python:3.12-slim

WORKDIR /app
RUN pip install --no-cache-dir flask

COPY flag.txt /app
COPY chall/app.py /app

CMD ["python", "app.py"]
