#! /usr/bin/bash
# Write a shell script to print 
# multiplication table of a number which is given by user.

echo "Printing Multiplication Table"
read -p "Enter number(n): " num 


for (( i=1; i<=10; i++ ))
do
echo "$(expr $num \* $i)"
done
echo
