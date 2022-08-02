use strict;
my %counts = {};

while (<STDIN>) {
  if (/GET \/ongoing\/When\/\d\d\dx\/(\d\d\d\d\/\d\d\/\d\d\/[^ .]+) /)
  {
    $counts{$1}++;
  }
}

my @k = keys(%counts);
my @k = sort { $counts{$b} <=> $counts{$a} } @k;
my $i;
foreach $i (0 .. 9)
{
  print "$counts{@k[$i]}: $k[$i]\n";
}


