#!/bin/bash
# Checks for 3 duplicate lines in scripts.
# Suggest these lines are possible replaced
# by a function.
#
tempfile=$2
#
#
sed -n '{
1N; N; 
s/ //g; s/\t//g; 
s/\n/\a/g; p; 
s/\a/\n/; D}' $1 >> $tempfile
#
sort $tempfile | uniq -d | sed 's/\a/\n/g'
#
rm -i $tempfile 
#
exit
