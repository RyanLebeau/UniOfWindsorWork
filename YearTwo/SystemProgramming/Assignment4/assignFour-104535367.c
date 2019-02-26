/*
Ryan Lebeau
19/11/2017
System Programming
assignFour-104535367.c
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/types.h>

void inputColour(char *, int *);
void red(int **);
void blue(int **);
void green(int **);
void yellow(int **);
void orange(int **);
void cyan(int **);
void magenta(int **);
void ocean(int **);
void violet(int **);
void sigHandler(int);

bool static writeFlag = false;
static int *diaCounter;

int main(int argc, char **argv){
	int k=0;
	int image = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	char p6[] = "P6\n1000 1000\n255\n";
	diaCounter = mmap(NULL, sizeof *diaCounter, PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);
	signal(SIGALRM, sigHandler);
	pid_t pid;
	
	//parent
	if ((pid=fork()) > 0){
		sleep(4);
		write(image, &p6, 17);
		//return to child
		kill(pid, SIGALRM);
	} 
	else{
		signal(SIGALRM, sigHandler);
		pause();
		//after parent has signaled for the beginning of file writing
		if(writeFlag){
			//child process 1
			for(int i=0; i<100; i++){
				for(int j=0; j<1000; j++){
					if(j<500)
						inputColour(argv[3], &image);
					else
						inputColour(argv[4], &image);
				}
			}
			//creating the next 9 child processes
			for(;k<9;k++){
				pid = fork();
				if(pid==0)
					break;
			}
			//within each child process
			if(pid==0){
				switch(k){
					//child process 2
					case 0:
						printf("Drawing...");
						sleep(k);
						for(int i=0; i<100; i++){
							for(int j=0; j<1000; j++){
								if(j<500)
									inputColour(argv[3], &image);
								else
									inputColour(argv[4], &image);
							}
						}
						break;
					//child process 3
					case 1:
						sleep(k);
						for(int i=0; i<100; i++){
							//if(i>=50)
								//diaCounter++;
							for(int j=0; j<1000; j++){
								if(j<500 && i<50)
									inputColour(argv[3], &image);
								else if(j>=500 && i<50)
									inputColour(argv[4], &image);
								else{
									if(j<(500-*diaCounter)){
										inputColour(argv[3], &image);
									}
									else if(j>(500+*diaCounter)){
										inputColour(argv[4], &image);
									}
									else if(j>=(500-*diaCounter) && j<=(500+*diaCounter)){
										inputColour(argv[2], &image);
									}
								}
							}
							if(i>=50)
								*diaCounter+=1;
						}
						break;
					//child process 4
					case 2:
						sleep(k);
						for(int i=0; i<100; i++){
							//diaCounter++;
							for(int j=0; j<1000; j++){
								if(j<(500-*diaCounter)){
									inputColour(argv[3], &image);
								}
								else if(j>(500+*diaCounter)){
									inputColour(argv[4], &image);
								}
								else if(j>=(500-*diaCounter) && j<=(500+*diaCounter)){
									inputColour(argv[2], &image);
								}
							}
							*diaCounter+=1;
						}
						break;
					//child process 5
					case 3:
						sleep(k);
						for(int i=0; i<100; i++){
							for(int j=0; j<1000; j++){
								if(j<(500-*diaCounter)){
									inputColour(argv[3], &image);
								}
								else if(j>(500+*diaCounter)){
									inputColour(argv[4], &image);
								}
								else if(j>=(500-*diaCounter) && j<=(500+*diaCounter)){
									inputColour(argv[2], &image);
								}
							}
							*diaCounter+=1;
						}
						break;
					//child process 6
					case 4:
						sleep(k);
						for(int i=0; i<100; i++){
							for(int j=0; j<1000; j++){
								if(j<(500-*diaCounter)){
									inputColour(argv[5], &image);
								}
								else if(j>(500+*diaCounter)){
									inputColour(argv[6], &image);
								}
								else if(j>=(500-*diaCounter) && j<=(500+*diaCounter)){
									inputColour(argv[2], &image);
								}
							}
							*diaCounter-=1;
						}
						break;
					//child process 7
					case 5:
						sleep(k);
						for(int i=0; i<100; i++){
							for(int j=0; j<1000; j++){
								if(j<(500-*diaCounter)){
									inputColour(argv[5], &image);
								}
								else if(j>(500+*diaCounter)){
									inputColour(argv[6], &image);
								}
								else if(j>=(500-*diaCounter) && j<=(500+*diaCounter)){
									inputColour(argv[2], &image);
								}
							}
							*diaCounter-=1;
						}
						break;
					//child process 8
					case 6:
						sleep(k);
						for(int i=0; i<100; i++){
							for(int j=0; j<1000; j++){
								if(j<500 && i>50)
									inputColour(argv[5], &image);
								else if(j>=500 && i>50)
									inputColour(argv[6], &image);
								else{
									if(j<(500-*diaCounter)){
										inputColour(argv[5], &image);
									}
									else if(j>(500+*diaCounter)){
										inputColour(argv[6], &image);
									}
									else if(j>=(500-*diaCounter) && j<=(500+*diaCounter)){
										inputColour(argv[2], &image);
									}
								}
							}
							if(i<=50)
								*diaCounter-=1;
						}
						break;
					//child process 9
					case 7:
						sleep(k);
						for(int i=0; i<100; i++){
							for(int j=0; j<1000; j++){
								if(j<500)
									inputColour(argv[5], &image);
								else
									inputColour(argv[6], &image);
							}
						}
						break;
					//child process 10
					case 8:
						sleep(k);
						printf("Completed.\n");
						for(int i=0; i<100; i++){
							for(int j=0; j<1000; j++){
								if(j<500)
									inputColour(argv[5], &image);
								else
									inputColour(argv[6], &image);
							}
						}
						break;
					//no child process to run
					default:
						printf("you messed up.\n");
						break;
				}
			}
		}
	}
	
	close(image);
}

void sigHandler(int signum){
	writeFlag = true;
}

//handles drawing pixel defined by colour entered in
void inputColour(char *colour, int *image){
	if(strcmp(colour, "blue")==0)
		blue(&image);
	else if(strcmp(colour, "red")==0)
		red(&image);
	else if(strcmp(colour, "green")==0)
		green(&image);
	else if(strcmp(colour, "yellow")==0)
		yellow(&image);
	else if(strcmp(colour, "orange")==0)
		orange(&image);
	else if(strcmp(colour, "cyan")==0)
		cyan(&image);
	else if(strcmp(colour, "magenta")==0)
		magenta(&image);
	else if(strcmp(colour, "ocean")==0)
		ocean(&image);
	else if(strcmp(colour, "violet")==0)
		violet(&image);
	else
		printf("That is not a valid colour.");
}

//ALL DRAWING FUNCTIONS
void red(int **image){
	char unsigned red = 255;
	char unsigned green = 0;
	char unsigned blue = 0;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}

void blue(int **image){
	char unsigned red = 0;
	char unsigned green = 0;
	char unsigned blue = 255;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}

void green(int **image){
	char unsigned red = 0;
	char unsigned green = 255;
	char unsigned blue = 0;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}

void yellow(int **image){
	char unsigned red = 255;
	char unsigned green = 255;
	char unsigned blue = 0;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}

void orange(int **image){
	char unsigned red = 255;
	char unsigned green = 153;
	char unsigned blue = 0;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}

void cyan(int **image){
	char unsigned red = 0;
	char unsigned green = 255;
	char unsigned blue = 255;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}

void magenta(int **image){
	char unsigned red = 255;
	char unsigned green = 0;
	char unsigned blue = 255;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}

void ocean(int **image){
	char unsigned red = 0;
	char unsigned green = 119;
	char unsigned blue = 190;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}

void violet(int **image){
	char unsigned red = 138;
	char unsigned green = 43;
	char unsigned blue = 226;
	write(**image, &red, 1);
	write(**image, &green, 1);
	write(**image, &blue, 1);
}