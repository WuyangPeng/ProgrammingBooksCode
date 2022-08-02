#!/bin/bash
# Testing a double parentheses command 
#
val1=10
#
if (( $val1 ** 2 > 90 ))
then
     (( val2 = $val1 ** 2 ))
     echo "The square of $val1 is $val2,"
     echo "which is greater than 90."
#
fi
