#!/bin/bash
# testing the for variable after the looping
 
for test in Alabama Alaska Arizona Arkansas California Colorado
do
   echo "The next state is $test"
done
echo "The last state we visited was $test"
test=Connecticut
echo "Wait, now we're visiting $test"
