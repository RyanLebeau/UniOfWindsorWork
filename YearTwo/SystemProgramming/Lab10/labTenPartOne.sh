#!/bin/bash
str=$(ls)
arr=(${str// / })
echo "shell command and array practice" ${arr[@]}
echo "total number of files and directories: " ${#arr[@]}
echo "first element in the array: " ${arr[0]}
echo "all elements in the array:"
for i in "${arr[@]}"
do
	echo $i
done
exit 0