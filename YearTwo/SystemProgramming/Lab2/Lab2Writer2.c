/*
Ryan Lebeau
27/09/2017
System Programming
Lab2Writer2.c
*/

#include <fcntl.h>
#include <unistd.h>

int main(void){
	int file = open("list2.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
	char text[]="GM\t101\tBuick\t2010\nFord\t102\tLincoln\t2005";
	write(file, &text, 43);
	close(file);
}