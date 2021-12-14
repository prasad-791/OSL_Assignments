#!/bin/bash

vehicle=$1

case $vehicle in
	"car" )
		echo "Rent of $vehicle is 100 dollar" ;;
	"van" )
		echo "Rent of $vehicle is 50 dollar" ;;
	"cycle" )
		echo "Rent of $vehicle is 30 dollar" ;;
	"truck" )
		echo "Rent of $vehicle is 1000 dollar" ;;
	*)
		echo "Unknown Vehicle";;
esac
