#!/usr/bin/perl -w
use strict;
print "This is a simple Regular Expression Tester.\n";
print "First, enter the pattern you want to test.\n";
print "Remember NOT to escape metacharacters like \\d with an extra \\ when you supply a pattern on the command line.\n";
print "Enter your pattern here: ";
my $myPattern = <STDIN>;
chomp($myPattern);
print "The pattern being tested is '$myPattern'.";
print "Enter a test string:\n";
while (<>)
{
 chomp();
 if (/$myPattern/)
 {
  print "Matched '$&' in '$_'\n";
  print "\nEnter another test string (or Ctrl+C to terminate):";
 }
 else
 {
  print "No match was found for '$myPattern' in '$_'.\n";
  print "\nEnter another test string (or Ctrl+C to terminate):";
 }
}