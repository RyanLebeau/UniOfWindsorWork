/*
Ryan Lebeau
01/11/2017
System Programming
labSixPTwo.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//Part 2
int main(int argc, char **argv){
	argc-=1;
	for(int i=0; i<=argc/2; i++){
		if(fork()==0){
			sleep(i);
			char *args[]={argv[i*2+1], argv[i*2+2], NULL};
			printf("Process ID: %d\n", getpid());
			execvp(args[0], args);
		}
	}
}

