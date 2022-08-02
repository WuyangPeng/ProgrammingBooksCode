#!/bin/bash
# Using one command-line parameter
#
factorial=1
for (( number = 1; number <= $1; number++ ))
do
     factorial=$[ $factorial * $number ]
done
echo The factorial of $1 is $factorial
exit
 
