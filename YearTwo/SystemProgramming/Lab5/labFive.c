/*
Ryan Lebeau
24/10/2017
System Programming
labFive.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//Part One

int main(int argc, char **argv){
	//converting inputs to integers
	int intArgs[7] = {0};
	int counter=0;
	for(int i=0; i<argc-1; i++){
		intArgs[i] = atoi(argv[i+1]);
	}
	//process 2
	if(fork() == 0){
		//process 4
		if(fork() == 0){
			sleep(intArgs[3]);
			printf("process 4 terminated, pid=%d\n", getpid());
			exit(0);
		}
		//process 5
		else{
			if(fork() == 0){
				sleep(intArgs[4]);
				printf("process 5 terminated, pid=%d\n", getpid());
				exit(0);
			}
		}
		sleep(intArgs[1]);
		printf("process 2 terminated, pid=%d\n", getpid());
		exit(0);
	}
	//process 1
	else{
		//process 3
		if(fork() == 0){
			sleep(intArgs[2]);
			printf("process 3 terminated, pid=%d\n", getpid());
			exit(0);
		}
		else{
			//process 6
			if(fork() == 0){
				sleep(intArgs[5]);
				printf("process 6 terminated, pid=%d\n", getpid());
				exit(0);
			}
			//process 7
			else{
				if(fork() == 0){
					sleep(intArgs[6]);
					printf("process 7 terminated, pid=%d\n", getpid());
					exit(0);
				}
			}
		}
		sleep(intArgs[0]);
		printf("process 1 terminated, pid=%d\n", getpid());
		exit(0);
	}
	
}



