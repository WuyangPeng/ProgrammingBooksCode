#!/usr/bin/perl -w
use strict;
my $myPattern = "(Jim|Fred|Alice)";
print "Enter your first name here: \n";
my $myTestString = <STDIN>;
chomp($myTestString);
if ($myTestString =~ m/$myPattern/)
{
 print "Hello $&. How are you?";
}
else
{
 print "I am sorry, $myTestString. I don't know you.";   
}