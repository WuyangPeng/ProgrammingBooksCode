#!/usr/bin/perl -w
use strict;
print "This tests negative lookahead.\n";
print "Enter a test string here: ";
my $myTestString = <STDIN>;
chomp($myTestString);
if ($myTestString =~ m/Star(?! Training)/)
{
 print "There was a match which was '$&'.";
}
else
{
 print "There was no match.";
}