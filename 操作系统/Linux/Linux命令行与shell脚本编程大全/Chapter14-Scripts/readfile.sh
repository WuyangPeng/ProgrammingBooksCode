#!/bin/bash
# Using the read command to read a file
#
count=1
cat $HOME/scripts/test.txt | while read line
do
     echo "Line $count: $line"
     count=$[ $count + 1 ]
done
echo "Finished processing the file."
exit
