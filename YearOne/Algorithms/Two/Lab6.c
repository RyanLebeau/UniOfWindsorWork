/*
Ryan Lebeau
08/03/2017
Lab6.c
*/

#include <stdio.h>
#include <string.h>

//A
/*
int main(void){
	//creating the char arrays
	char buffer1[] = {'t','h','i','s',' ','i','s',' ','t','h','e',' ','f','i','r','s','t',' ','b','u','f','f','e','r','\0'};
	char buffer2[] = "this is the second buffer";
	char buffer3[80];
	//storing sting in 'buffer3'
	scanf("%[^\n]", buffer3);
	//printing all buffer strings
	printf("\n%s\n", buffer1);
	printf("%s\n", buffer2);
	printf("%s\n", buffer3);
	//initializing pointer and setting it to 'buffer3'
	char *pBuffer;
	pBuffer = buffer3;
	//printing 'buffer3' using pointer
	printf("\n%s\n", pBuffer);
	*pBuffer++;
	//printing from incremented pointer
	printf("%s", pBuffer);
	return 0;
}
*/

//B
/*
void Reverse(char[]);
int main(void){
	//initiating char array
	char text[] = {'h','e','l','l','o','\0'};
	printf("Before reverse: %s", text);
	Reverse(text);
	printf("\nAfter reverse: %s", text);
}
/*
Objective: Reverse inputted string
Input: Char array
Output: Array that has been reversed
*/
/*
void Reverse(char text[]){
	//the length of array 'text'
	int length = strlen(text);
	//creating duplicate array to reverse from
	char text2[80];
	strcpy(text2, text);
	//loop that runs entire length of char array 'text'
	for (int i=0;i<length;i++){
		//seeting current element of text to opposite element in duplicate array
		text[i] = text2[length-1-i];
	}
}
*/

//C

void parseSentence(char[]);
int main(void){
	//initializing the char array
	char text[]="hello world, how are you today.";
	parseSentence(text);
	
}

/*
Objective: Seperate string into words on seperate lines at delimiters
Input: Char array 'text'
Output: Each word at delimiter printed to seperate lines
*/

void parseSentence(char text[]){
	//getting length of string
	int length = strlen(text), print = 0;
	//loop that finds delimiters and prints
	for (int i=0;i<length;i++){
		//if current element of 'text' is a delimiter
		if (text[i]==' ' || text[i]==',' || text[i]==';' || text[i]=='.'){
			//add one to delimiter counter
			print++;
			//if repeating delimiters there will be no additional blank lines
			if (print>1)
				NULL;
			//create a new line
			else
				printf("\n");
		}
		//if no delimiter print current element of 'text'
		else{
			//reset delimiter counter
			print=0;
			printf("%c", text[i]);
		}
	}
}








