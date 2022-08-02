#!/bin/bash
# Shifting mulitiple positions through the parameters
#
echo 
echo "The original parameters: $*"
echo "Now shifting 2..."
shift 2
echo "Here's the new first parameter: $1"
echo
exit
