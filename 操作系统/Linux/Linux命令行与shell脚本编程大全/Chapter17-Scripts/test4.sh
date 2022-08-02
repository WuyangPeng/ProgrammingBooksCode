#!/bin/bash
# testing the exit status of a function

func1() {
   echo "trying to display a non-existent file"
   ls -l badfile
}

echo "testing the function: "
func1
echo "The exit status is: $?"
