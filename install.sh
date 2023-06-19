#!/bin/bash

# Getting IP address from argument
export TARGET_IP=$1
#export TARGET_IP=$TARGET_IP

# Installing game
make run

# Cleaning garbage
make clean

exit 0