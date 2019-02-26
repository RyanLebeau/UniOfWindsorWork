/*
Ryan Lebeau
26/02/2018
AssignThree.c
COMP 3300
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#define MSGSIZE 8

int* bubbleSort(int[],int);
int persistance(int, int);
int* largest(int[]);
int* smallest(int[]);
char* msg = "GO_AHEAD";

int main(int argc, char* argv[]){
	//time of program launch
	double time_spent = 0;
	clock_t begin = clock();
	
	//declring variables and creating pipes
	int oneP[2], twoP[2], threeP[2], fourP[2], fiveP[2], pids[5], count=10, ppid = getpid(), status;
	char* msgRec;
	pipe(oneP); pipe(twoP); pipe(threeP); pipe(fourP); pipe(fiveP);
	//handle nonbuffered I/O for parent
	setbuf(stdout,NULL);
	
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
	
	//seperating array into 5 parts
	int one[25],two[25],three[25],four[25],five[25];
	memcpy(one, sortNums, 25*sizeof(int));
	memcpy(two, &sortNums[25], 25*sizeof(int));
	memcpy(three, &sortNums[50], 25*sizeof(int));
	memcpy(four, &sortNums[75], 25*sizeof(int));
	memcpy(five, &sortNums[100], 25*sizeof(int));

	
	//creating all five children then breaking from loop
	for(int i=0;i<5;i++){
		if((pids[i]=fork())==0){
			setbuf(stdout,NULL);
			count=i+1;
			break;
		}
	}
	
	//parent gets caught here
	if(getpid() == ppid){
		printf("I am the father of %d, %d, %d, %d, and %d\n\n", pids[0], pids[1], pids[2], pids[3], pids[4]);
		//parent sends token to first child
		close(oneP[0]);
		write(oneP[1], &msg, MSGSIZE);
		close(oneP[1]);
	}

	//children get caught here
	if(getppid() == ppid){
		while(1){
			//child one
			if(count==1){
				//reading from the pipe
				close(oneP[1]);
				read(oneP[0], &msgRec, sizeof(msgRec));
				close(oneP[0]);
				if(!strcmp(msgRec, msg)){
					//inside child process
					printf("I am kid#:%d and my id is %d\n", count, getpid());
					//using the correct fifth of the sorted array per child
					int persis[25];
					//finding persistance of each number
					for(int i=0;i<25;i++){
						persis[i]=persistance(one[i],0);
						printf("%d persistance %d\n", one[i], persis[i]);
					} 
					//storing position and value of smallest/largest persistance
					int* smallStuff = smallest(persis), *largeStuff = largest(persis);
					//printing out each number based off of position and its persistance
					printf("\n%d has the smallest persistance %d\n%d has the largest persistance %d\n", one[smallStuff[1]], smallStuff[0], one[largeStuff[1]], largeStuff[0]);
					
					//child passing token to next child
					close(twoP[0]);
					write(twoP[1], &msg, MSGSIZE);
					close(twoP[1]);
					exit(count);
				}
			}
			//child two
			if(count==2){
				//reading from the pipe
				close(twoP[1]);
				read(twoP[0], &msgRec, sizeof(msgRec));
				close(twoP[0]);
				if(!strcmp(msgRec, msg)){
					//inside child process
					printf("I am kid#:%d and my id is %d\n", count, getpid());
					//using the correct fifth of the sorted array per child
					int persis[25];
					for(int i=0;i<25;i++){
						persis[i]=persistance(two[i],0);
						printf("%d persistance %d\n", two[i], persis[i]);
					}
					int* smallStuff2 = smallest(persis), *largeStuff2 = largest(persis);
					printf("\n%d has the smallest persistance %d\n%d has the largest persistance %d\n", two[smallStuff2[1]], smallStuff2[0], two[largeStuff2[1]], largeStuff2[0]);
					
					//child passing token to next child
					close(threeP[0]);
					write(threeP[1], &msg, MSGSIZE);
					close(threeP[1]);
					exit(count);
				}
			}
			//child three
			if(count==3){
				//reading from the pipe
				close(threeP[1]);
				read(threeP[0], &msgRec, sizeof(msgRec));
				close(threeP[0]);
				if(!strcmp(msgRec, msg)){
					//inside child process
					printf("I am kid#:%d and my id is %d\n", count, getpid());
					//using the correct fifth of the sorted array per child
					int persis[25];
					for(int i=0;i<25;i++){
						persis[i]=persistance(three[i],0);
						printf("%d persistance %d\n", three[i], persis[i]);
					}
					int* smallStuff3 = smallest(persis), *largeStuff3 = largest(persis);
					printf("\n%d has the smallest persistance %d\n%d has the largest persistance %d\n", three[smallStuff3[1]], smallStuff3[0], three[largeStuff3[1]], largeStuff3[0]);
					
					//child passing token to next child
					close(fourP[0]);
					write(fourP[1], &msg, MSGSIZE);
					close(fourP[1]);
					exit(count);
				}
			}
			//child four
			if(count==4){
				//reading from the pipe
				close(fourP[1]);
				read(fourP[0], &msgRec, sizeof(msgRec));
				close(fourP[0]);
				if(!strcmp(msgRec, msg)){
					//inside child process
					printf("I am kid#:%d and my id is %d\n", count, getpid());
					//using the correct fifth of the sorted array per child
					int persis[25];
					for(int i=0;i<25;i++){
						persis[i]=persistance(four[i],0);
						printf("%d persistance %d\n", four[i], persis[i]);
					}
					int* smallStuff4 = smallest(persis), *largeStuff4 = largest(persis);
					printf("\n%d has the smallest persistance %d\n%d has the largest persistance %d\n", four[smallStuff4[1]], smallStuff4[0], four[largeStuff4[1]], largeStuff4[0]);
					
					//child passing token to next child
					close(fiveP[0]);
					write(fiveP[1], &msg, MSGSIZE);
					close(fiveP[1]);
					exit(count);
				}
			}
			//child five
			if(count==5){
				//reading from the pipe
				close(fiveP[1]);
				read(fiveP[0], &msgRec, sizeof(msgRec));
				close(fiveP[0]);
				if(!strcmp(msgRec, msg)){
					//inside child process
					printf("I am kid#:%d and my id is %d\n", count, getpid());
					//using the correct fifth of the sorted array per child
					int persis[25];
					for(int i=0;i<25;i++){
						persis[i]=persistance(five[i],0);
						printf("%d persistance %d\n", five[i], persis[i]);
					}
					int* smallStuff5 = smallest(persis), *largeStuff5 = largest(persis);
					printf("\n%d has the smallest persistance %d\n%d has the largest persistance %d\n", five[smallStuff5[1]], smallStuff5[0], five[largeStuff5[1]], largeStuff5[0]);
					exit(count);
				}
			}
		}
	}
	
	//inside parent
	while(1){
		if (wait(&status) >= 0){
			if (WIFEXITED(status)){
				//which child exited with what code, they force exit with code 0
				printf("----From the main: child, id %d ended with status %d\n", pids[WEXITSTATUS(status)-1], WEXITSTATUS(status));
			}
			if(WEXITSTATUS(status)==5)
				break;
		}
	}
	
	//calculating final CPU usage time
	clock_t end = clock();
	time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
	printf("Time elpased is %f seconds\n", time_spent);
	printf("Goodbye!");
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

//recursive function which finally returns persistance once number reaches one digit
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

//takes in the array of persistances and returns the largest one and its position
int* largest(int persist[]){
	int position, large=persist[0];
	//setting memory for array so it can be returned
	int *stuff = malloc(2 * sizeof(int));
	//find largest persistance
	for(int i=0;i<25;i++){
		if(persist[i]>large){
			large=persist[i];
			position=i;
		}
	}
	//add both position and persistance to stuff array
	stuff[0]=large;stuff[1]=position;
	return stuff;
}

//takes in the array of persistances and returns the smallest one and its position
int* smallest(int persist[]){
	int position, small=persist[0];
	//setting memory for array so it can be returned
	int *stuff = malloc(2 * sizeof(int));
	//find smallest persistance
	for(int i=0;i<25;i++){
		if(persist[i]<small){
			small=persist[i];
			position=i;
		}
	}
	//add both position and persistance to stuff array
	stuff[0]=small;stuff[1]=position;
	return stuff;
}





