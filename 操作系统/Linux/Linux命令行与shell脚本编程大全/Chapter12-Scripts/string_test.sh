#!/bin/bash
# Using string test evaluations
#
testuser=christine
#
if [ $testuser = christine ]
then
     echo "The testuser variable contains: christine"
else
     echo "The testuser variable contains: $testuser"
fi
