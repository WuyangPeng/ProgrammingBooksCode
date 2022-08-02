#!/usr/bin/perl -w
use strict;
print "Enter a string. It will be matched against the pattern '/Star/i'.\n\n";
chomp (my $myTestString = <STDIN>);
print "There is a match for '$myTestString'." if ($myTestString =~ m/Star/i);
print "There is no match for '$myTestString'." if ($myTestString !~ m/Star/i);