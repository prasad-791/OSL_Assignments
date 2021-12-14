#!/bin/bash
# name of the file 
name_of_file=""

# create function to create or open a file
create(){
	echo ""
	echo -e "Enter file name for Address Book: \c" 
	read filename
	len=`expr length "$filename"`
	# checks if the file name entered by the user is not empty
	if test $len > 0;
	then
	# creates or opens a file
		name_of_file=$filename 
		touch $filename
		echo -e "\nFile with name $filename created/opened successfully"
	else 
		echo -e "\nFile Name cannot be empty"
	fi
}

# insert a record of the student in the given format
insert(){
	echo ""
	echo "Enter Name PhoneNo and City of the Person"
	# the format
	echo "format: firstname lastname PhoneNo City"
	read firstname lastname phoneNo city
	echo "$firstname $lastname $phoneNo $city" >>$name_of_file
			
	echo "Data added Successfully"
}

# display the records
display(){
	echo ""
	echo "The Records are as follows"
	echo ""
	cat $name_of_file | while read p
	do
		echo $p
	done
}

# to delete a particular record
delete(){
	
	# checks if the value of a particular record, given to the function is present or not
	if grep -q $1 $name_of_file;
	then
		# if it is present then the line/record is deleted
		sed -i "/$1/d" $name_of_file	
		echo "Record deleted successfully"
	else 
		# if not present then this message is shown to the user
		echo "No such student with Roll No $1 present"
	fi
}

# to modify details of a particular record
modify(){
	# checks if the value of a particular record, given to the function is present or not
	ans=`grep -n $2 $name_of_file | cut -d : -f 1`
	if grep -q $2 $name_of_file;
	then 
		if test $1 == 1;
		then 
			# if it is present then new record is replaced in place of that record
			echo "Enter new FirstName LastName Phone City"
			read value
			sed -i "s/.*$2.*/$value/" $name_of_file
			echo "Record modified successfully"
		else
			# only that particular value is replaced
			echo "Enter the current value of the user that is to be replaced"
			read value
			echo "Enter new value for it"
			read newvalue
			sed -i "$ans s/$value/$newvalue/" $name_of_file
			echo "Record modified successfully"
		fi
	else 
		echo "No such student with Roll No $2 present"
	fi
}

# to search for a particular record
search(){
	ans=`grep $1 $name_of_file`
	if grep -q $1 $name_of_file;
	then
		echo "Record found, the record is as follows"
		echo "$ans"
	else
		echo "Record not found"
	fi
}

while [ true ] ;
do	
	# the choices for the user
	echo ""
	echo "Enter 1 to create/open a database"
	echo "Enter 2 to add a record"
	echo "Enter 3 to display all records"
	echo "Enter 4 to delete a record"
	echo "Enter 5 to modify whole record"
	echo "Enter 6 to modify a particular value of that record"
	echo "Enter 7 to search a record"
	echo "Enter 8 to exit"
	
	# the choice is taken as an input
	read -p 'Enter choice: ' value
	case $value in
		"1" )	
			# to create or open a file
			create ;;
			
		"2" )	
			# to insert records into that file
			insert ;;	
			
		"3" )
			# to display all the records of that file
			display ;;
		"4" )
			# to delete a record based on Phone No
			echo ""
			echo "Enter the Phone No of User whose record is to be deleted"
			read phone
			delete $phone
		;;
		"5" ) 
			# to modify a whole record based on given phone no
			echo ""
			echo "Enter the Phone No of User whose deatils are to be modified"
			read phone
			modify 1 $phone 
		;;
		"6" )
			# to modify a particular value of that record of a given phone no
			echo ""
			echo "Enter the Phone No of User whose deatils are to be modified"
			read phone
			modify 2 $phone 
		;;
		"7" )
			# to search a record based on phone no
			echo ""
			echo "Enter the Phone No of User whose record is to be searched"
			read phone
			search $phone
		;;
		"8" )	
			# to exit the menu
			echo ""
			echo "Quitting"
			exit 
		;; 
		* ) 
			# invalid choice
			echo "Wrong Input" ;;
	esac
done
