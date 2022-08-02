#!/bin/bash
#Testing restarting a 2nd job 
#
count=1
while [ $count -le 5 ]
do
     #echo "Loop #$count"
     sleep 10
     count=$[ $count + 1 ]
done
#
echo "This is the script's end."
exit
