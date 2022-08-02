#!/bin/bash
# Check if object exists and is a directory or a file
#
object_name=$HOME/sentinel
echo
echo "The object being checked: $object_name"
echo
#
if [ -e $object_name ]
then
     echo "The object, $object_name, does exist,"
     #
     if [ -f $object_name ]
     then
          echo "and $object_name is a file."
     #
     else
          echo "and $object_name is a directory."
     fi
#
else
     echo "The object, $object_name, does NOT exist."
fi
