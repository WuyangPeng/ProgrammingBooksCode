#!/bin/bash
#Test script to use with trapandrun.sh
#
echo "This is a test script."
#
count=1
while [ $count -le 5 ]
do
     echo "Loop #$count"
     sleep 10
     count=$[ $count + 1 ]
done
#
echo "This is the end of test script."
#exit
