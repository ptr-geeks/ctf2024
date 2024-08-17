const express = require('express');
const router = express.Router();
const db = require('./db');


router.get('/', async (req, res) => {
	const posts = await db.getPosts();
	res.render('index', { user: req.session.user, posts });
});

router.get('/login',async (req, res) => {
	if (req.session.user) {
		res.redirect('/');
		return;
	}

	res.render('login', { user: req.session.user });
});

router.post('/login', async (req, res) => {
	const { username, password } = req.body;
	if (!username || !password) {
		res.json({ success: false, error: 'Invalid username or password' });
		return;
	}

	const user = await db.getUser({
		username,
		password,
	});

	if (!user) {
		res.json({ success: false, error: 'Invalid username or password' });
		return;
	}

	req.session.user = username;
	await req.session.save();
	res.json({ success: true });
});

router.get('/register',async (req, res) => {
	if (req.session.user) {
		res.redirect('/');
		return;
	}

	res.render('register', { user: req.session.user });
});

router.post('/register', async (req, res) => {
	const { username, password } = req.body;
	const user = await db.getUser({
		username,
	});

	if (user) {
		res.json({ success: false, error: 'Username already exists' });
		return;
	}

	await db.createUser({
		username,
		password,
	});

	req.session.user = username;
	await req.session.save();
	res.json({ success: true });
});

router.get('/logout',async (req, res) => {
	if (!req.session.user) {
		res.redirect('/');
		return;
	}

	req.session.destroy();
	res.redirect('/');
});

router.get('/new',async (req, res) => {
	if (!req.session.user) {
		res.redirect('/');
		return;
	}

	res.render('new', { user: req.session.user });
});

router.post('/new', async (req, res) => {
	const { title, content } = req.body;

	if (!req.session.user) {
		res.json({ success: false, error: 'Not logged in' });
		return;
	}

	if (!title || !content) {
		res.json({ success: false, error: 'Title or content missing' });
		return;
	}

	const user = await db.getUser(req.session.user);

	await db.createPost({
		title,
		content,
		createdAt: new Date(),
		authorId: user.id,
	});

	res.json({ success: true });
});

router.get('/post/:id', async (req, res) => {
	let post = await db.getPost(parseInt(req.params.id));
	post = post[0];
	if (!post) {
		res.redirect('/');
		return;
	}

	res.render('post', { user: req.session.user, post });
});

router.get('/flag', async (req, res) => {
	if (!req.session.user || req.session.user !== 'admin') {
		res.redirect('/');
		return;
	}

	const flag = process.env.FLAG || 'ptr{fake_flag}';
	res.json({ flag });
});

module.exports = router;
