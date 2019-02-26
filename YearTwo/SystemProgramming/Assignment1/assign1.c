/*
Ryan Lebeau
08/10/2017
System Programming
assign1.c
*/

#include <fcntl.h>
#include <unistd.h>

void mergePictures(int*, int*, int*, int*, int*);
void checkDimensions(int*, int*, int*);

int main(int argc, char **argv){
	int decimalOne=0,decimalTwo=0,whCounter=0,w1=0,h1=0,w2=0,h2=0,sumW,sumH;
	//opening both .ppm images
	int fileOne=open(argv[1], O_RDWR);
	int fileTwo=open(argv[2], O_RDWR);
	//to beginniing
	lseek(fileOne, 3, SEEK_SET);
	lseek(fileTwo, 3, SEEK_SET);
	//checking dimensions of images
	checkDimensions(&w1, &h1, &fileOne);
	checkDimensions(&w2, &h2, &fileTwo);
	//if pic2 is bigger than pic1
	if(w1<w2 || h1<h2){
		char err[] = "Error: Image 2 is not smaller than image 1.";
		write(STDOUT_FILENO, err, 43);
		return -1;
	}
	//skip graphics maximum line
	lseek(fileOne, 4, SEEK_CUR);
	lseek(fileTwo, 4, SEEK_CUR);
	//merges fileTwo to fileOne
	mergePictures(&w1,&w2,&h2,&fileOne,&fileTwo);
	//changing finished file name
	link(argv[1], argv[3]);
	unlink(argv[1]);
	//closing both image files
	close(fileOne);
	close(fileTwo);
}

void checkDimensions(int*w, int*h, int*file){
	int decimal=0, whCounter=0, sizew=0 ,sizeh=0, width[10]={0}, height[10]={0};
	//populating width and height array with correct ascii values
	while(decimal!=10){
		read(*file, &decimal, 1);
		//space is change between width and height
		if (decimal==32)
			whCounter = 1;
		//new line signals finish of width and height
		else if (decimal==10)
			break;
		//reading width
		else if (!whCounter){
			width[sizew] = decimal-48;
			sizew++;
		}
		//reading height
		else{
			height[sizeh] = decimal-48;
			sizeh++;
		}
	}
	//converting width array to value
	for (int k=0; k<sizew; k++){
		*w = 10*(*w)+width[k];
	}
	//converting height array to value
	for (int k=0; k<sizeh; k++){
		*h = 10*(*h)+height[k];
	}
}

void mergePictures(int*w1, int*w2, int*h2, int*fileOne, int*fileTwo){
	int tempByte=0;
	//runs pixel height
	for(int i=0;i<*h2;i++){
		//seek to right corner since 3bytes per pixel in a .ppm image
		lseek(*fileOne, (*w1-*w2)*3, SEEK_CUR);
		//once at corner copy fileTwo to fileOne byte by byte
		for (int k=0; k<*w2*3; k++){
			read(*fileTwo, &tempByte, 1);
			write(*fileOne, &tempByte, 1);
		}
	}
}
