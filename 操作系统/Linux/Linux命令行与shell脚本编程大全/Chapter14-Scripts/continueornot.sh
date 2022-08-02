#!/bin/bash
# Using the read command for one character
#
read -n 1 -p "Do you want to continue [Y/N]? " answer
#
case $answer in
Y | y) echo
       echo "Okay. Continue on...";;
N | n) echo
       echo "Okay. Goodbye"
       exit;;
esac
echo "This is the end of the script."
exit
