#!/bin/bash

n=1
until [ $n -ge 10 ]
do
	echo -e "$n "
	n=$((n+1))
done

select name in Aniket Prasad Rahul Rohan
do
 echo "$name selected "
done
