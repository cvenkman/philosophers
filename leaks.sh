#!/bin/bash

for ((;;))
do
	clear
	leaks philo | grep -A10 for
	sleep 1
done