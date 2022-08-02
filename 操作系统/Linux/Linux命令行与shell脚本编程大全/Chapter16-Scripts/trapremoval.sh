#!/bin/bash
#Removing a set trap 
#
trap "echo ' Sorry...Ctrl-C is trapped.'" SIGINT
#
count=1
while [ $count -le 3 ]
do
     echo "Loop #$count"
     sleep 1
     count=$[ $count + 1 ]
done
#
trap -- SIGINT
echo "The trap is now removed."
#
count=1
while [ $count -le 3 ]
do
     echo "Second Loop #$count"
     sleep 1
     count=$[ $count + 1 ]
done
#
exit
