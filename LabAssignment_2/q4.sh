#! /usr/bin/bash
# Write a shell script to print Fibonacci series.

echo "Printing Fibonacci Series up to N terms..."
read -p "Enter number(N): " num 

f0=0
f1=1
fib=0
echo -e "$f0 $f1 \c"

for (( i=2; i<=$num; i++ ))
do
fib=$(( f0+f1 ))
f0=$(( f1 ))
f1=$(( fib ))

echo -e "$fib \c"
done
echo
