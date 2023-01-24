#! /usr/bin/bash

echo "Finding sum up to N..."
read -p "Enter number(N): " num 
sum=0

until [ $num -eq 0 ]
do
sum=$(( sum+num ))
num=$(( num-1 ))
done
 
echo "sum = $sum" 