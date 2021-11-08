#!/bin/bash

for ((;;))
do
	clear
	leaks a.out | grep -A10 for
	sleep 1
done