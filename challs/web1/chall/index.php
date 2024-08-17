<?php
	session_start();

	if (isset($_COOKIE['username'])) {
		header('Location: home.php');
		exit();
	}

	if ($_SERVER['REQUEST_METHOD'] === 'POST') {
		$username = $_POST['username'];
		$password = $_POST['password'];
		$submit = $_POST['submit'];

		if ($submit === 'Log in' && $username === 'admin' && $password === $_ENV['ADMIN_PASSWORD']) {
			setcookie('username', $username);
			header('Location: home.php');
			exit();
		} else if ($submit === 'Anonymous login') {
			setcookie('username', 'Anonymous');
			header('Location: home.php');
			exit();
		} else {
			$error = 'Invalid username or password';
		}
	}
?>
<!DOCTYPE html>
<html>
<head>
	<title>Log in</title>
	<link rel="stylesheet" type="text/css" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
</head>
<body>
	<div class="container">
		<div class="row">
			<div class="col-md-6">
				<h2>Log in</h2>
				<form action="/" method="post">
					<div class="form-group">
						<label for="username">Username</label>
						<input type="text" name="username" class="form-control">
					</div>
					<div class="form-group">
						<label for="password">Password</label>
						<input type="password" name="password" class="form-control">
					</div>
					<input type="submit" name="submit" value="Log in" class="btn btn-primary">
					<input type="submit" name="submit" value="Anonymous login" class="btn btn-secondary">
				</form>
				<?php if (isset($error)): ?>
					<div class="alert alert-danger" role="alert">
						<?= $error ?>
					</div>
				<?php endif; ?>
			</div>
		</div>
	</div>
</body>
