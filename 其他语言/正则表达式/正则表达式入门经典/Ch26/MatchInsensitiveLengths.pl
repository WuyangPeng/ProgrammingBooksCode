#!/usr/bin/perl -w
use strict;
print "Enter a string. It will be matched against the pattern '/Star/i'.\n\n";
my $myTestString = <STDIN>;
my $myLength = length($myTestString);
print "The length before chomp() is $myLength.\n\n";
chomp($myTestString);
$myLength = length($myTestString);
print "The length after chomp() is $myLength.\n\n";

if ($myTestString =~ m/Star/i)
{
 print "There is a match for '$myTestString'.\n\n";
}
else
{
 print "No match was found in '$myTestString'.";
}