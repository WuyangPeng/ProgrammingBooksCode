<html>
<head>
<title>ereg() [:alnum:] Test</title>
</head>
<body>
<?php
$match = ereg('[[:alnum:]]+', "Hello world!", $matches);
if ($match)
{ 
 echo "<p>A match was found.</p>";
 echo "<p>$matches[0]</p>";
}
?>
</body>
</html>