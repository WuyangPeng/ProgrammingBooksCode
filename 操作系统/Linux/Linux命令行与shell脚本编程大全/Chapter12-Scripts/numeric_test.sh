#!/bin/bash
# Using numeric test evaluations
#
value1=10
value2=11
#
if [ $value1 -gt 5 ]
then
     echo "The test value $value1 is greater than 5."
fi
#
if [ $value1 -eq $value2 ]
then 
     echo "The values are equal."
else
     echo "The values are different."
fi
