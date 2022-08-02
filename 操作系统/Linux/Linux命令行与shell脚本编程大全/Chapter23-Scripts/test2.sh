#!/bin/dash
# testing the = comparison
 
test1=abcdef
test2=abcdef
 
if [ $test1 = $test2 ]
then
   echo "They're the same!"
else
   echo "They're different"
fi
