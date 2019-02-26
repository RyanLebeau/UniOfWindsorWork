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

int main(void){
	int storage = open("storage.txt", O_RDWR), storageNum;
	//read in number from storage.txt
	char storageStr[2];
	read(storage, &storageStr, 2);
	//change to integer and decrease ny 3
	storageNum = atoi(storageStr);
	storageNum -= 3;
	//change int back to string then write over with new value in storage.txt
	snprintf(storageStr, 10, "%d", storageNum);
	lseek(storage, 0, SEEK_SET);
	write(storage, &storageStr, 2);
	printf("from consumer: total is %s\n", storageStr);
	//creating a child process to run producer bash script
	if(fork()==0){
		sleep(1);
		char *args[]={"./producer.sh", NULL};
		execvp(args[0], args);
		exit(0);
	}
}