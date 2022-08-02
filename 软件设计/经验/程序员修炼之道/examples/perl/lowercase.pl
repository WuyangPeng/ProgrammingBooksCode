#!/usr/bin/perl -w
#
# From "Text Manipulation",
# Convert files in current directory with uppercase names to lower case
#

use strict;


#START:body
foreach (<*>) {
  if (-f && ($_ eq uc($_))) {
    rename $_, lc($_) or die "Can't rename $_: $!"
  }
}
#END:body
  
