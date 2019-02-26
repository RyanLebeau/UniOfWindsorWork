/*
Ryan Lebeau
01/11/2017
System Programming
labSixPOne.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//Part 1
int main(void){
	char *args[]={"./mybash.sh", NULL};
	printf("EXAM! EXAM! EXAM!\n");
	if (fork()==0){
		execvp(args[0], args);
	}
	
}
