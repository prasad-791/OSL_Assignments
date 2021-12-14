#!/bin/bash

read -p 'Enter Username: ' user_name
echo "Username: $user_name"

password=""
character=""
echo -n "Enter password: "
while true;
do
	read -n1 -s chr
	character="$chr"
	if [ "$chr" != '' && $character != "\n" ]; then
		echo -n "*"
		password+="${chr}"
	else 
		break
	fi
done
echo "Password: $password"
echo "done"
