<?php
if(isset($_GET['action'])){
	if($_GET['action'] == 'ping'){
		$ip = $_GET['ip'];
		$cmd = "ping -c 4 '$ip'";
		$output = shell_exec($cmd);
	}
	if($_GET['action'] == 'dns'){
		$domain = $_GET['domain'];
		$cmd = "nslookup '$domain'";
		$output = shell_exec($cmd);
	}
	if($_GET['action'] == 'ct'){
		$domain = $_GET['domain'];
		$cmd = "curl -s 'https://ctlog.si/api/v1/logs/domain/$domain' | jq -r '.[].domain'";
		$output = shell_exec($cmd);
	}
}
?>
<!DOCTYPE html>
<html>
<head>
	<title>Toolbox</title>
	<link rel="stylesheet" type="text/css" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
</head>
<body>
	<div class="container">
		<div class="row">
			<div class="col-md-6">
				<h2>Ping</h2>
				<form>
					<div class="form-group">
						<label>IP Address</label>
						<input type="text" name="ip" class="form-control">
						<input type="hidden" name="action" value="ping">
					</div>
					<button type="submit" class="btn btn-primary">Ping</button>
				</form>
				<br/>
				<h2>DNS lookup</h2>
				<form>
					<div class="form-group">
						<label>Domain</label>
						<input type="text" name="domain" class="form-control">
						<input type="hidden" name="action" value="dns">
					</div>
					<button type="submit" class="btn btn-primary">Lookup</button>
				</form>
				<h2>.si Transparency logs</h2>
				<form>
					<div class="form-group">
						<label>Domain</label>
						<input type="text" name="domain" class="form-control">
						<input type="hidden" name="action" value="ct">
					</div>
					<button type="submit" class="btn btn-primary">Lookup</button>
				</form>
			</div>
			<?php if(isset($output)): ?>
			<div class="col-md-6">
				<h2>Output</h2>
				<pre><?php echo $output; ?></pre>
			</div>
			<?php endif; ?>
		</div>
	</div>
</body>
