/*
Ryan Lebeau
05/11/2017
System Programming.c
consumer.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void sigHandler(){};

int main(int argc, char **argv){
	int file = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	printf("parent opened file: %s\n", argv[1]);
	char first[] = "EXAM!EXAM!EXAM!\n";
	char second[] = "HELP!HELP!HELP!\n";
	char third[] = "STUDY!STUDY!STUDY!\n";
	
	if(fork()==0){
		printf("parent created child process: %d\n", getpid());
		write(file, &first, 17);
		printf("%d has written to file: %s", getpid(), first);
		sleep(5);
		kill(getpid(), SIGALRM);
	}
	else{
		if(fork()==0){
			printf("parent created child process: %d\n", getpid());
			signal(SIGALRM, sigHandler);
			write(file, &second, 17);
			printf("%d has written to file: %s", getpid(), second);
			sleep(5);
			kill(getpid(), SIGALRM);
		}
		else{
			sleep(5);
			signal(SIGALRM, sigHandler);
			write(file, &third, 19);
			printf("parent has written to file: %s", third);
			close(file);
			printf("parent closed the file");
		}
	}
		
}