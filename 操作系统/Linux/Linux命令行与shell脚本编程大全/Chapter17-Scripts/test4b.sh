#!/bin/bash
# testing the exit status of a function

func1() {
   ls -l badfile
   echo "This was a test of a bad command"
}

echo "testing the function:"
func1
echo "The exit status is: $?"
