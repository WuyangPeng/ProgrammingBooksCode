#!/bin/bash
# Using string test not equal evaluations
#
testuser=rich
#
if [ $testuser != christine ]
then
     echo "The testuser variable does NOT contain: christine"
else
     echo "The testuser variable contains: christine"
fi
