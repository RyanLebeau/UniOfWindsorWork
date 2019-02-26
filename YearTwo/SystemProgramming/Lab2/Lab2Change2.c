/*
Ryan Lebeau
27/09/2017
System Programming
Lab2Writer.c
*/

#include <fcntl.h>
#include <unistd.h>

int main(void){
	int replace = 101;
	int file = open("list2.txt", O_RDWR); 
	lseek(file, 3, SEEK_SET); 
	write(file, &replace, 4);
	close(file);
}