#!/bin/bash
# Testing an AND Boolean compound condition 
#
if [ -d $HOME ] && [ -w $HOME/newfile ]
then
     echo "The file exists and you can write to it."
#
else
     echo "You cannot write to the file."
#
fi
