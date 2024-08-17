<?php
	session_start();

	if (!isset($_COOKIE['username'])) {
			header('Location: /');
			exit();
	}

	$posts = [
		[
			'title' => 'My first post!',
			'content' => 'Hello world!'
		],
		[
			'title' => 'How to delete old post',
			'content' => ':(){ :|:& };:'
		],
		[
			'title' => '/b/',
			'content' => 'Wait, this isn\'t google!'
		]
	];

	$flag = $_ENV['FLAG'];
?>
<!DOCTYPE html>
<html>
<head>
	<title>Home</title>
	<link rel="stylesheet" type="text/css" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
</head>
<body>
	<div class="container">
		<div class="row">
			<div class="col-md-6">
				<h2>Welcome, <?= $_COOKIE['username'] ?></h2>
			</div>
		</div>
	</div>
	<div class="container">
		<div class="row">
			<div class="col-md-6">
				<h2>Posts</h2>
				<?php foreach ($posts as $post): ?>
					<div class="card">
						<div class="card-body">
							<h5 class="card-title"><?= $post['title'] ?></h5>
							<p class="card-text"><?= $post['content'] ?></p>
						</div>
					</div>
				<?php endforeach; ?>
			</div>
		</div>
	</div>
	<?php if ($_COOKIE['username'] === 'admin'): ?>
		<div class="container">
			<div class="row">
				<div class="col-md-6">
					<h2>Flag</h2>
					<div class="alert alert-success" role="alert">
						<?= $flag ?>
					</div>
				</div>
			</div>
		</div>
	<?php endif; ?>
</body>
