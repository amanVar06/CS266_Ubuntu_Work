#! /usr/bin/bash
# Write a shell script to 
# check whether an input is a prime or not.

echo "Checking if the number is prime or not..."
read -p "Enter number(N): " num 
cnt=0

for (( i=2; $(expr $i \* $i )<$num; i++ ))
do
if [ $(expr $num % $i ) -eq 0 ]
then
(( cnt++ ))
fi 
done

if [ $cnt -eq 0 ]
then
echo "Entered number is a prime number."
else
echo "Entered number is not a prime number."
fi
