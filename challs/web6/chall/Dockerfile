FROM node:22-alpine

ENV FLAG=ptr{fake_flag}
WORKDIR /app

COPY package*.json .

RUN npm ci --omit=dev

COPY .env /app
COPY src /app/src
COPY views /app/views
COPY prisma /app/prisma

RUN npx prisma generate

CMD ["node", "src/index.js"]
