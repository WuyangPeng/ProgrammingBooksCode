#!/usr/bin/perl -w
use strict;
print "Enter a string. It will be matched against the pattern '/Star/i'.\n\n";
chomp (my $myTestString = <STDIN>);
if ($myTestString =~ m/Star/i)
{
 print "There is a match for '$myTestString'.";
}
else
{
 print "No match was found in '$myTestString'.";
}