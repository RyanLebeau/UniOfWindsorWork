/*
Ryan Lebeau
27/09/2017
System Programming
Lab2Writer.c
*/

#include <fcntl.h>
#include <unistd.h>

int main(void){
	int file = open("list1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
	char text[]="101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005";
	write(file, &text, 43);
	close(file);
}
