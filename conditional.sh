#!/bin/bash
if [ $# -eq 0 ];
then 
	echo "Enter 1 integer"
fi

if test $1 -gt 0;
then
	echo "$1 is positive"
elif test $1 -lt 0;
then 
	echo "$1 is negative"
else
	echo "$1 is zero"
fi
