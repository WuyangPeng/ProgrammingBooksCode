#!/bin/bash
# Testing a single parentheses condition 
#
echo $BASH_SUBSHELL
#
if (echo $BASH_SUBSHELL)
then
     echo "The subshell command operated successfully."
#
else
     echo "The subshell command was NOT successful."
#
fi
