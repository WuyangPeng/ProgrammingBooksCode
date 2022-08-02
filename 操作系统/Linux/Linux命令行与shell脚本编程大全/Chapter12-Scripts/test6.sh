#!/bin/bash
# testing if a variable has content
#
my_variable=""
#
if test $my_variable
then
     echo "The my_variable variable has content and returns a True."
     echo "The my_variable variable content is: $my_variable"
else 
     echo "The my_variable variable doesn't have content,"
     echo "and returns a False."
fi
