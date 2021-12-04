#!/bin/sh

while true; do
	dmesg | tail
	echo ''
	sleep 1
done
