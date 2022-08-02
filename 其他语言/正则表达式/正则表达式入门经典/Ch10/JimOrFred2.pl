#!/usr/bin/perl -w
use strict;
print "This program will say 'Hello' to Jim or Fred.\n";
my $myPattern = "
^    # Matches the position before the first character on the line
(Jim # Literally matches 'Jim'
|    # The alternation character
Fred)# Literally matches 'Fred'
\$"  # Matches the position after the last character on the line
;
# The pattern matches only 'Jim' or 'Fred'. Nothing else is allowed.
print "Enter your first name here: ";
my $myTestString = <STDIN>;
chomp ($myTestString);
if ($myTestString =~ m/$myPattern/x)
{
 print "Hello $myTestString. How are you today?";
}
else
{
 print "Sorry I don't know you!";
}