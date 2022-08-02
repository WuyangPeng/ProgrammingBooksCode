#!/bin/bash
# testing nested ifs - using elif
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
fi
echo "We are outside the nested if statements."

