#!/bin/bash
# Check if a file is empty
#
file_name=$HOME/sentinel
echo
echo "Checking if $file_name file is empty..."
echo 
#
# Check if file exists and is a file.
#
if [ -f $file_name ]
then
     # File does exist. Check if it is empty.
     #
     if [ -s $file_name ]
     then
          echo "The $file_name file exists and has data in it."
          echo "Will not remove this file."
     #
     else
          echo "The $file_name file exits, but is empty."
          echo "Deleting empty file..."
          rm $file_name
     fi
#
else
     echo "The $file_name file does not exist."
fi
