#! /usr/bin/bash
# Write a shell script to find 
# whether an input integer is even or odd.

read -p "Enter your number: " num 
echo "you have entered $num"

if [ $(( num % 2 )) -eq 0 ]
then
echo "the entered number is even"
else
echo "the entered number is odd"
fi
