#!/bin/bash

while read p
do
	echo $p
done < demo.sh

cat hello.sh | while read p
do
	echo $p
done
