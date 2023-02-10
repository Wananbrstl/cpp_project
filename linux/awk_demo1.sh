#! /usr/bin/bash

# useage
# awk ' condition {action}' file for every line
# print the $2>170's name 
awk '$2>170 {print $1}' test.txt
