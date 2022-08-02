#!/bin/bash
# testing nested ifs - using elif and else
#
testuser=NoSuchUser
#
if grep $testuser /etc/passwd
then
     echo "The user $testuser account exists on this system."
     echo
elif ls -d /home/$testuser/
     then 
          echo "The user $testuser has a directory,"
          echo "even though $testuser doesn't have an account."
     else
          echo "The user $testuser does not exist on this system,"
          echo "and no directory exists for the $testuser."
fi
echo "We are outside the nested if statements."

