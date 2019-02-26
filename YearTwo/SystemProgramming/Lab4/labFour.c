/*
Ryan Lebeau
18/10/2017
System Programming
labFour.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
	int data = open("data.dat", O_RDWR | O_CREAT | O_TRUNC);
	int enteredNum, factorial=1;
	int flag=0;
	pid_t pid;
	pid=fork();
	//printf("%d\n", pid);
	if(pid==-1){
		printf("Error");
		exit(1);
	}
	else if (pid==0){
		enteredNum = atoi(argv[1]);
		//printf("%d", flag);
		if(enteredNum>=1 && enteredNum<=10){
			for(int i=1; i<= enteredNum; i++){
				factorial*=i;
			}
			
			
		}
		printf("Factorial of %d is %d.", enteredNum, factorial);
		exit(0);
	}
	else {
		enteredNum = atoi(argv[1]);
		sleep(1);

		if (enteredNum>=1 && enteredNum<=10){
			write(data, argv[1], 2);
		}
		else
			printf("Error, number out of range.");
		exit(1);
	}
	
	
}