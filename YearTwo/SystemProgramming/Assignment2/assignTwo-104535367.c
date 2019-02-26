/*
Ryan Lebeau
29/10/2017
System Programming
assignTwo.c
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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

int main(int argc, char **argv){
	//process 1 - ppm info
	int diaCounter=0;
	int image = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	char p6[] = "P6\n1000 1000\n255\n";
	write(image, &p6, 17);

	//process 2 - first 100lines
	if(fork() == 0){
		sleep(1);
		for(int i=0; i<100; i++){
			for(int j=0; j<1000; j++){
				if(j<500)
					inputColour(argv[3], &image);
				else
					inputColour(argv[4], &image);
			}
			
		}
		//process 3
		if(fork() == 0){
			sleep(2);
			for(int i=0; i<100; i++){
				for(int j=0; j<1000; j++){
					if(j<500)
						inputColour(argv[3], &image);
					else
						inputColour(argv[4], &image);
				}
			}
			//process 4
			if(fork()==0){
				sleep(2);
				for(int i=0; i<100; i++){
					//if(i>=50)
						//diaCounter++;
					for(int j=0; j<1000; j++){
						if(j<500 && i<50)
							inputColour(argv[3], &image);
						else if(j>=500 && i<50)
							inputColour(argv[4], &image);
						else{
							if(j<(500-diaCounter)){
								inputColour(argv[3], &image);
							}
							else if(j>(500+diaCounter)){
								inputColour(argv[4], &image);
							}
							else if(j>=(500-diaCounter) && j<=(500+diaCounter)){
								inputColour(argv[2], &image);
							}
						}
					}
					if(i>=50)
						diaCounter++;
				}
				//process 5
				if(fork()==0){
					sleep(2);
					for(int i=0; i<100; i++){
						//diaCounter++;
						for(int j=0; j<1000; j++){
							if(j<(500-diaCounter)){
								inputColour(argv[3], &image);
							}
							else if(j>(500+diaCounter)){
								inputColour(argv[4], &image);
							}
							else if(j>=(500-diaCounter) && j<=(500+diaCounter)){
								inputColour(argv[2], &image);
							}
						}
						diaCounter++;
					}
					//process 6
					if(fork()==0){
						sleep(2);
						for(int i=0; i<100; i++){
							//diaCounter++;
							for(int j=0; j<1000; j++){
								if(j<(500-diaCounter)){
									inputColour(argv[3], &image);
								}
								else if(j>(500+diaCounter)){
									inputColour(argv[4], &image);
								}
								else if(j>=(500-diaCounter) && j<=(500+diaCounter)){
									inputColour(argv[2], &image);
								}
							}
							diaCounter++;
						}
						//process 7
						if(fork()==0){
							sleep(2);
							for(int i=0; i<100; i++){
								//diaCounter--;
								for(int j=0; j<1000; j++){
									if(j<(500-diaCounter)){
										inputColour(argv[5], &image);
									}
									else if(j>(500+diaCounter)){
										inputColour(argv[6], &image);
									}
									else if(j>=(500-diaCounter) && j<=(500+diaCounter)){
										inputColour(argv[2], &image);
									}
								}
								diaCounter--;
							}
							//process 8
							if(fork()==0){
								sleep(2);
								for(int i=0; i<100; i++){
									//diaCounter--;
									for(int j=0; j<1000; j++){
										if(j<(500-diaCounter)){
											inputColour(argv[5], &image);
										}
										else if(j>(500+diaCounter)){
											inputColour(argv[6], &image);
										}
										else if(j>=(500-diaCounter) && j<=(500+diaCounter)){
											inputColour(argv[2], &image);
										}
									}
									diaCounter--;
								}
								//process 9
								if(fork()==0){
									sleep(2);
									for(int i=0; i<100; i++){
										//diaCounter--;
										for(int j=0; j<1000; j++){
											if(j<500 && i>50)
												inputColour(argv[5], &image);
											else if(j>=500 && i>50)
												inputColour(argv[6], &image);
											else{
												if(j<(500-diaCounter)){
													inputColour(argv[5], &image);
												}
												else if(j>(500+diaCounter)){
													inputColour(argv[6], &image);
												}
												else if(j>=(500-diaCounter) && j<=(500+diaCounter)){
													inputColour(argv[2], &image);
												}
											}
										}
										if(i<=50)
											diaCounter--;
									}
									//process 10
									if(fork() == 0){
										sleep(2);
										for(int i=0; i<100; i++){
											for(int j=0; j<1000; j++){
												if(j<500)
													inputColour(argv[5], &image);
												else
													inputColour(argv[6], &image);
											}
										}
										//process 11
										if(fork() == 0){
											sleep(2);
											printf("Completed.");
											for(int i=0; i<100; i++){
												for(int j=0; j<1000; j++){
													if(j<500)
														inputColour(argv[5], &image);
													else
														inputColour(argv[6], &image);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	close(image);
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
