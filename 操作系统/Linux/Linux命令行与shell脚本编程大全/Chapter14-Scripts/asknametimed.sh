#!/bin/bash
# Using the read command with a timer
#
if read -t 5 -p "Enter your name: " name
then
     echo "Hello $name, welcome to my script."
else
     echo
     echo "Sorry, no longer waiting for name."
fi
exit
