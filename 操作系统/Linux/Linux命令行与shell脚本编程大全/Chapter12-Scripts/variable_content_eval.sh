#!/bin/bash
# Testing string length
#
string1=Soccer
string2=''
#
if [ -n $string1 ]
then
     echo "The string '$string1' is NOT empty"
else
     echo "The string '$string1' IS empty"
fi
#
if [ -z $string2 ]
then
     echo "The string '$string2' IS empty"
else
     echo "The string '$string2' is NOT empty"
fi
#
if [ -z $string3 ]
then
     echo "The string '$string3' IS empty"
else
     echo "The string '$string3' is NOT empty"
fi
