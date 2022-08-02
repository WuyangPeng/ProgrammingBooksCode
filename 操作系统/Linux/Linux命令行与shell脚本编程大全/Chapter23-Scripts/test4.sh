#!/bin/zsh
# using the repeat command
 
value1=$(( 10 / 2 ))
repeat $value1
do
   echo "This is a test"
done
