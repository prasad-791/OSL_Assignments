#!/bin/bash
echo -e "Welcome to OS lecture\n"
echo -e "Today is `date` \n"
echo -e "Enter name: "
read name
echo -e "Name: $name \n"
read -p 'Enter username: ' user_name
echo -e "UserName: $user_name \n"
read -s -p 'Enter password: ' password
echo -e "\nPassword: $password \n"
echo -e "Enter city names\n"
read -a names
echo -e "City Names are: ${names[0]},${names[1]},${names[2]} \n"
number=70
class="TE-09"
echo -e "There are $number in Class $class \n"
ls
