const { PrismaClient } = require('@prisma/client')

const prisma = new PrismaClient()


async function getUser(where) {
	const users = await prisma.user.findMany({
		where,
	})

	if (users.length === 0) {
		return null
	}
	return users[0]
}

async function createUser(data) {
	return await prisma.user.create({
		data,
	})
}


async function getPosts(filter) {
	return await prisma.post.findMany(filter)
}

async function getPost(id) {
	return await prisma.post.findMany({
		where: {
			id,
		},
		select: {
			id: true,
			title: true,
			content: true,
			createdAt: true,
			author: {
				select: {
					username: true,
				},
			},
		},
	})

	if (posts.length === 0) {
		return null
	}
	return posts[0]
}

async function createPost(data) {
	return await prisma.post.create({
		data,
	})
}


module.exports = {
	getUser,
	createUser,
	getPosts,
	getPost,
	createPost,
}
