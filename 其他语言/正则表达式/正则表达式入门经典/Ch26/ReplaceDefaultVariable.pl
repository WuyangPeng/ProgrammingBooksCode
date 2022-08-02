#!/usr/bin/perl -w
use strict;
$_ = "I went to a training course from Star Training Company.";
print "The default string, \$_, contains '$_'.\n\n";
if (s/Star/Moon/)
{
 print "A replacement has taken place using the default variable.\n";
 print "The replaced string in \$_ is now '$_'.";
}