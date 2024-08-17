FROM node:22-alpine

ENV FLAG=ptr{fake_flag}
WORKDIR /app

COPY chall/package*.json .

RUN npm ci --omit=dev

COPY chall/.env /app
COPY chall/src /app/src
COPY chall/views /app/views
COPY chall/prisma /app/prisma

RUN npx prisma generate

CMD ["node", "src/index.js"]
