#!/bin/bash
# Using a tedious and long if statement 
#
if [ $USER == "rich" ]
then
     echo "Welcome $USER"
     echo "Please enjoy your visit."
elif [ $USER == "barbara" ]
then 
     echo "Hi there, $USER"
     echo "We're glad you could join us."
elif [ $USER == "christine" ]
then 
     echo "Welcome $USER"
     echo "Please enjoy your visit."
elif [ $USER == "tim" ]
then
     echo "Hi there, $USER"
     echo "We're glad you could join us."
elif [ $USER = "testing" ]
then
     echo "Please log out when done with test."
else
     echo "Sorry, you are not allowed here."
fi
