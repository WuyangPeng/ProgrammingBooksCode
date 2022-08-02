#!/usr/bin/perl -w
use strict;
print "\nThis example demonstrates the use of the ^ and \$ positional metacharacters.\n\n";
my $myPattern = "cape";
my $myTestString = "escape";
print "In '$myTestString' there is a match for the pattern '$myPattern'.\n\n" if ($myTestString =~ m/$myPattern/);

$myPattern = "^cape";
print "When the pattern is '$myPattern' there is no match for '$myTestString'.\n\n" if ($myTestString !~ m/$myPattern/);
$myPattern = "cape\$";
print "But there is a match for '$myTestString' when the pattern is '$myPattern'.\n\n" if ($myTestString =~ m/$myPattern/);