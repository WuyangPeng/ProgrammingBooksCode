#!/bin/bash
# Extract command-line options and parameters with getopts
#
echo 
while getopts :ab:cd opt
do
     case "$opt" in
          a) echo "Found the -a option" ;;
          b) echo "Found the -b option with parameter value $OPTARG";;
          c) echo "Found the -c option" ;;
          d) echo "Found the -d option" ;;
          *) echo "Unknown option: $opt" ;;
     esac
done
#
shift $[ $OPTIND - 1 ]
#
echo
count=1
for param in "$@"
do
     echo "Parameter $count: $param"
     count=$[ $count + 1 ]
done
exit
