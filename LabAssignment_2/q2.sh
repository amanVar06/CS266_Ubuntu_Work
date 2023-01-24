#! /usr/bin/bash
# Write a shell script to find whether an 
# input year is leap year or not.

echo -e "Enter the year: \c"
read year
if [ $(( year % 400  )) -eq 0 ]
then
echo "Entered year is a leap year."
elif [ $(( year % 100  )) -eq 0 ]
then
echo "Entered year is not a leap year."
elif [ $(( year % 4  )) -eq 0 ]
then
echo "Entered year is a leap year."
else
echo "Entered year is not a leap year."
fi
