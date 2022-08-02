#!/bin/bash
# Testing a process list 
#
echo $BASH_SUBSHELL
#
if (echo $BASH_SUBSHELL; ls /etc/PASSWORD; pwd)
then
     echo "The subshell commands operated successfully."
#
else
     echo "The subshell commands were NOT successful."
#
fi
