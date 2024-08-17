const express = require('express');
const session = require('express-session');
const { PrismaClient } = require('@prisma/client');

const routers = require('./routers');
const utils = require('./utils');

const app = express();
const prisma = new PrismaClient();


const user = prisma.user.findUnique({
	where: {
		username: 'admin',
	}
}).then((user) => {
	if (!user) {
		console.log('Creating admin user');
		prisma.user.create({
			data: {
				username: 'admin',
				password: utils.randomString(32),
			},
		}).then(() => {
			console.log('Admin user created');
		}).catch((error) => {
			console.error('Error creating admin user', error);
		});
	}
});



app.set('trust proxy', 1)
app.set('view engine', 'ejs');
app.set('views', './views');

app.use(express.json());
app.use(session({
	secret: utils.randomString(64),
	cookie: { sameSite: true },
	saveUninitialized: true,
	resave: true,
}));

app.use(routers);

app.listen(8000, () => {
	console.log('Server is running on http://localhost:8000');
});
