#!/bin/bash
storageNum=$(<storage.txt)
if (($((storageNum + 8)) < 100)); then
	newNum=$((storageNum + 8))
	echo "from producer: total is $newNum"
	echo $newNum > "storage.txt"
	./a.exe
else
	echo "from producer: Now I will take a rest!"
	exit 0
fi
