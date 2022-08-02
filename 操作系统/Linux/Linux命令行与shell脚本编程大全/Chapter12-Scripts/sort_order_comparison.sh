#!/bin/bash
# Testing string sort order
#
string1=Soccer
string2=soccer
#
if [ $string1 \> $string2 ]
then
     echo "$string1 is greater than $string2"
else
     echo "$string1 is less than $string2"
fi
