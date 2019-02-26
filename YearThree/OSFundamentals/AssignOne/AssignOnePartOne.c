/*
Ryan Lebeau
22/01/2018
AssignOnePartOne.c
COMP 3300
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int* bubbleSort(int[],int);
int persistance(int, int);

int main(int argc, char* argv[]){
	//time of program launch
	double time_spent = 0;
	clock_t begin = clock();
	
	//if no parameter given
    if(argc==1){
		printf("You need to enter in a text file name");
		return 0;
	}
	
	//scanning in all numbers from text file
	int n=125;
	int nums[n];
	FILE *txtPtr = fopen(argv[1], "r");
	for(int i=0;i<n;i++){
		fscanf(txtPtr, "%d", &nums[i]);
	}
	
	//sorted array
	int *sortNums = bubbleSort(nums, n);
	int persis[n];
	printf("Persistance of all numbers: \n");
	//add persistance of each number to array
	for(int i=0;i<n;i++){
		persis[i]=persistance(sortNums[i],0);
		printf("%d persistance %d\n", sortNums[i], persis[i]);
	}
	
	
	//smallest and largest persistance
	int small, large, pos[2]={0};
	small=persis[0];
	large=persis[0];
	for(int i=0;i<n;i++){
		if(persis[i]<small){
			small=persis[i];
			pos[0]=i;
		}
		else if(persis[i]>large){
			large=persis[i];
			pos[1]=i;
		}
	}
	printf("\n%d has the smallest persistance %d\n%d has the largest persistance %d\n", sortNums[pos[0]], small, sortNums[pos[1]], large);

	//calculating final CPU usage time
	clock_t end = clock();
	time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
	printf("\nTime elpased is %f seconds", time_spent);
	return 0;
}

//sorting from smallest to largest
int* bubbleSort(int nums[], int n){
	int temp;
	//simple bubblesort loops
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(nums[j]>nums[j+1]){
				temp=nums[j];
				nums[j]=nums[j+1];
				nums[j+1]=temp;
			}
		}
	}
	return nums;
}

int persistance(int num, int count){
	int newNum=1, digit=0, len;
	char numS[9], digitC;
	//convert number to string
	sprintf(numS, "%d", num);
	len=strlen(numS);
	//if length of string is one (down to one digit)
	if(len==1)
		return count;
	//access each char of string(digit) and mutliply to newNum
	for(int i=0;i<len;i++){
		digit=numS[i] - '0';
		newNum*=digit;
	}

	//recursion until newNum is only one digit, then return persistance
	return persistance(newNum, count+1);
}



