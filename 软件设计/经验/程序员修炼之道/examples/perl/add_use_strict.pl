#!/usr/bin/perl -w
#
# From "Text Manipulation",
# adds a 'use strict' to all Perl scripts currently missing one.
# Assumes that an existing one starts in column one (so the
# comment above doesn't count).
#
# Passed a directory to search. Only looks at .pl files

use strict;

#START:body
my $dir = shift or die "Missing directory";

for my $file (glob("$dir/*.pl")) {

  open(IP, "$file") or die "Opening $file: $!";
  undef $/;           # Turn off input record separator --
  my $content = <IP>; # read whole file as one string.
  close(IP);

  if ($content !~ /^use strict/m) {

    rename $file, "$file.bak" or die "Renaming $file: $!";
    open(OP, ">$file") or die "Creating $file: $!";
    
    # Put 'use strict' on first line that
    # doesn't start '#'
    $content =~ s/^(?!#)/\nuse strict;\n\n/m;

    print OP $content;
    close(OP);

    print "Updated $file\n";
  }
  else {
    print "$file already strict\n";
  }
}
#END:body
