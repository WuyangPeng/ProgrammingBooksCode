#!/bin/bash
# Testing a single parentheses condition 
#
#echo $BASH_SUBSHELL
#
if (cat /etc/PASSWORD)
then
     echo "The subshell command operated successfully."
#
else
     echo "The subshell command was NOT successful."
#
fi
