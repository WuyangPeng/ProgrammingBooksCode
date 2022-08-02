#!/bin/sh
#
# From "Shell Games",
# Example shell script that finds the unique package names
# in a set of Java files
#

(cd ../java
#START:body
grep '^import ' *.java | 
  sed -e's/.*import  *//' -e's/;.*$//' | 
  sort -u >list
#END:body
)

cat ../java/list
rm ../java/list
