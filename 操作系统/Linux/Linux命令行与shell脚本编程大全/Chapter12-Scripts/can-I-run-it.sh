#!/bin/bash
# Check if you can run a file
#
item_name=$HOME/scripts/can-I-write-to-it.sh
echo
echo "Checking if you can run $item_name..."
#
# Check if file is executable.
#
if [ -x $item_name ]
then
     echo "You can run $item_name."
     echo "Running $item_name..."
     $item_name
#
else
     echo "Sorry, you cannot run $item_name."
#
fi
