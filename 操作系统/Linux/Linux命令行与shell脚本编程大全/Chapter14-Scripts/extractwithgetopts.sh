#!/bin/bash
# Extract command-line options and values with getopts
#
echo 
while getopts :ab:c opt
do
     case "$opt" in
          a) echo "Found the -a option" ;;
          b) echo "Found the -b option with parameter value $OPTARG";;
          c) echo "Found the -c option" ;;
          *) echo "Unknown option: $opt" ;;
     esac
done
exit
