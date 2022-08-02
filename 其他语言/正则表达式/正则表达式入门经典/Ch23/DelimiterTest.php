<html>
<head>
<title>Using preg_match() with different delimiters.</title>
</head>
<body>
<?php
if (preg_match("/Hel/", "Hello world!")) echo "<p>A match was found using paired '/' as delimiter.</p>";
if (preg_match(".Hel.", "Hello world!")) echo "<p>A match was found using paired '.' as delimiter.</p>";
if (preg_match("{Hel}", "Hello world!")) echo "<p>A match was found using matched '{' and '}' as delimiters.</p>";
if (preg_match("(Hel)", "Hello world!")) echo "<p>A match was found using matched '(' and ')' as delimiters.</p>";
if (preg_match("<Hel>", "Hello world!")) echo "<p>A match was found using matched '<' and '>' as delimiters.</p>";
?>
</body>
</html>