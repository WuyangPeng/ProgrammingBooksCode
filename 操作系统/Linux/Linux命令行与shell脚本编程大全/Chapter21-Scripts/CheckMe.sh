#!/bin/bash
# Demonstrating the need for functions
#
echo
if [ -z $1 ] || [ -z $2 ] 
then
	echo "Missing parameter"
	echo "Usage: ./CheckMe.sh parameter1 parameter2"
	echo "Exiting script..."
	exit
#
fi
#
echo "You entered the command correctly! You used:"
echo "Usage: ./CheckMe.sh parameter1 parameter2"
echo "Exiting script..."
exit
