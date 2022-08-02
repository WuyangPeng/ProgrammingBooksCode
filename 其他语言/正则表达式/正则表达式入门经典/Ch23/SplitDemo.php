<html>
<head>
<title>split() Function Demo</title>
</head>
<body>
<?php
$myString1 = "2004/09/23";
$myString2 = "2004.09.23";
$myString3 = "2004-09-23";
$myPattern = "[-/.]";
list($year, $month, $day) =  split($myPattern, $myString1); 
echo "<p>String was: $myString1. <br />Year: $year <br />Month: $month <br />Day: $day</p>";
list($year, $month, $day) =  split($myPattern, $myString2); 
echo "<br /><br /><p>String was: $myString2. <br />Year: $year <br />Month: $month <br />Day: $day</p>";
list($year, $month, $day) =  split($myPattern, $myString3); 
echo "<br /><br /><p>String was: $myString3. <br />Year: $year <br />Month: $month <br />Day: $day</p>";
?>
</body>
</html>