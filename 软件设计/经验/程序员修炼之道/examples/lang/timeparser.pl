#!/usr/bin/perl -w
use strict;

# From "Domain Languages",
# Parse a time in the format 
#
#  time -> hh am/pm   |
#          hh:mm      |
#          hh:mm am/pm
#
# print the number of minutes past midnight, or return -1 on error

#START:ans
$_ = shift;

/^(\d\d?)(am|pm)$/        && doTime($1, 0,  $2, 12);
/^(\d\d?):(\d\d)(am|pm)$/ && doTime($1, $2, $3, 12);
/^(\d\d?):(\d\d)$/        && doTime($1, $2,  0, 24);
die "Invalid time $_\n";

#
# doTime(hour, min, ampm, maxHour)
#
sub doTime($$$$) {
  my ($hour, $min, $offset, $maxHour) = @_;
  die "Invalid hour: $hour" if ($hour >= $maxHour);
  $hour += 12 if ($offset eq "pm");
  print $hour*60 + $min, " minutes past midnight\n";
  exit(0);
}
#END:ans
