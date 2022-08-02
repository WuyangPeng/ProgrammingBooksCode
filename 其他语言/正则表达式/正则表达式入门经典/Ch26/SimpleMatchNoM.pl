#!/usr/bin/perl -w
use strict;
my $myString = "Hello world!";
if ($myString =~ /world/)
{
 print "There was a match.";
}
else
{
 print "There was no match.";
}