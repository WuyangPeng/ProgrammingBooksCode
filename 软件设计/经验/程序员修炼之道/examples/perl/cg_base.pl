#!/usr/bin/perl -w
use strict;

# From "Code Generators",
# usage:  cg_base <language>  <flatfile
#  where <language> identifies a code generator called
#  <language>_cg.pl

# START:body
my $lang = shift or die "Missing language";
$lang .= "_cg.pm";

require "$lang" or die "Couldn't load $lang";

# Read and parse the file

my $name;

while (<>) {
  chomp;
  if    (/^\s*$/)     { CG::blankLine(); }
  elsif (/^\#(.*)/)   { CG::comment($1); }
  elsif (/^M\s*(.+)/) { CG::startMsg($1); $name = $1; }
  elsif (/^E/)        { CG::endMsg($name); }
  elsif (/^F\s*(\w+)\s+(\w+)$/)
                      { CG::simpleType($1,$2); }
  elsif (/^F\s*(\w+)\s+(\w+)\[(\d+)\]$/)
                      { CG::arrayType($1,$2,$3); }
  else {
    die "Invalid line: $_";
  }
}
# END:body


