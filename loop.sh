#!/bin/bash
echo "First loop"
for i in 1 2 3 4 5 6
do
	echo -n "$i "
done
echo -en "\nSecond loop\n"

for i in {1..10}
do 
	echo -n "$i "
done

echo -en "\nThird loop\n"

for i in {1..10..2}
do 
	echo -n "$i "
done

echo -en "\n4th loop\n"

for (( i=0; i<5; i++ ))
do 
	echo -n "$i "
done

echo -en "\nWhile loop\n"

n=1 
while [ $n -le 10 ];
do
	 echo -n "$n "
	 n=$((n+1))
done 

echo -en "\nPattern\n"

i=0
while [ $i -le 9 ];
do
	for (( j=$i; j>=0; j-- ))
	do
		echo -n "$j "
	done
	echo ""
	i=$((i+1))
done
echo ""


