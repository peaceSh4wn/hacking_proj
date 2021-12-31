#!/bin/sh

while true; do 
	dmesg | tail
	sleep 1
	echo ''
done
