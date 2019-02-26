/*
Ryan Lebeau
14/11/2017
System Programming
labEight.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char **argv){
	int file = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0755), fd[2], size=0;
	char text = 't';
	pipe(fd);
	if(fork()==0){
		close(fd[0]);
		close(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		sleep(2);
		execlp(argv[1], NULL);
	}
	else{
		close(fd[1]);
		while(read(fd[0], &text, 1) != 0){
			size++;
			write(file, &text, 1);
		}
		printf("\nThe result of %s has been written to 'output.txt' with %d bytes.", argv[1], size);
		close(file);
	}
}