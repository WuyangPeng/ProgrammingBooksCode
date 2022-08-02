<html>
<head>
<title>Using preg_match_all()</title>
</head>
<body>
<?php
$testString = "A99 B888 C234 D123 E45678 f2345";
$myMatches = preg_match_all("/[A-Z]\d{1,5}/", $testString, $partNumbers);
if ($myMatches)
{
 for($counter=0; $counter < $myMatches; $counter++)
 {
  if ($partNumbers[0][$counter] != "")
  {
   echo "<p>" . $partNumbers[0][$counter]. "</p>";
  }
 }
}
?>
</body>
</html>