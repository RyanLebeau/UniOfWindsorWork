#!/bin/bash
declare -a passArr212
declare -a passArr256
declare -a passBoth
counter=1
num=49
while read in212; do
	arr1=(${in212//	/ })
	if [[ ${arr1[1]} > "$num" ]]; then
		passArr212[$((counter-1))]=${arr1[0]}
	fi
	((counter+=1))
done <60-212.txt
counter=1
while read in256; do
	arr2=(${in256//	/ })
	if [[ ${arr2[1]} > "$num" ]]; then
		passArr256[$((counter-1))]=${arr2[0]}
	fi
	((counter+=1))
done <60-256.txt
if (( ${#passArr212[@]} <= ${#passArr256[@]} )); then
	for i in "${passArr212[@]}"; do
		for j in "${passArr256[@]}"; do
			#echo $j
			if (( i == j )); then
				passBoth[$((${#passBoth[@]}))]=$i
			fi	
		done
	done
else
	for i in "${passArr256[@]}"; do
		for j in "${passArr212[@]}"; do
			if (( i == j )); then
				passBoth[$((${#passBoth[@]}))]=$i
			fi	
		done
	done
fi
echo "Pass: ${passBoth[@]}"
exit 0