<html>
<head>
<title>Simple preg_match() Regex Test</title>
</head>
<body>
<?php
if (preg_match("/Hel/", "Hello world!")) echo "<p>A match was found using paired '/' as delimiter.</p>";
if (preg_match("{Hel}", "Hello world!")) echo "<p>A match was found using paired '/' as delimiter.</p>";
?>
</body>
</html>