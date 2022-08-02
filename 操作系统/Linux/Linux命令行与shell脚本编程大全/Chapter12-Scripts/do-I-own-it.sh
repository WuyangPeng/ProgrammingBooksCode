#!/bin/bash
# Check if you own a file
#
if [ -O /etc/passwd ]
then
     echo "You are the owner of the /etc/passwd file."
#
else
     echo "Sorry, you are NOT /etc/passwd file's owner."
#
fi
