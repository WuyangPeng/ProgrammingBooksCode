#!/bin/bash
# Adding command-line parameters
#
if [ $# -ne 2 ] 
then
     echo Usage: $(basename $0) parameter1 parameter2
else
     total=$[ $1 + $2 ]
     echo $1 + $2 is $total
fi
exit
