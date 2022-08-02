#!/bin/bash
# nesting for loops
 
for (( a = 1; a <= 3; a++ ))
do
   echo "Starting loop $a:"
   for (( b = 1; b <= 3; b++ ))
   do
      echo "   Inside loop: $b"
   done
done
