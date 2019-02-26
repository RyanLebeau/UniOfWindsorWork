/*
Ryan Lebeau
15/03/2017
Lab7.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A
//function declarations
/*
int AtoI ( const char * str );
int StrCmp ( const char * str1, const char * str2 );
char * StrCpy ( char * destination, const char * source );
char * StrCat ( char * destination, const char * source );
char * StrChr ( char * str, int character );

int main(void){
	//AtoI
	char *strAtoI = "12";
	int value = AtoI(strAtoI);
	printf("Before conversion: %s\n", strAtoI);
	printf("After conversion: %d\n-----\n", value);
	//StrCmp
	char *str1Cmp = "hallo", *str2Cmp = "hello";
	printf("%d\n-----\n", StrCmp(str1Cmp, str2Cmp));
	//StrCpy
	char destinationCpy[100],sourceCpy[] = "hello world";
	StrCpy(destinationCpy, sourceCpy);
	printf("%s\n-----\n", destinationCpy);
	//StrCat
	char destinationCt[200] = "hello", sourceCt[200] = "world";
	StrCat(destinationCt, sourceCt);
	printf("%s\n-----\n", destinationCt);
	//StrChr
	char *strChr = "hello world", character = ' ';
	printf("%s\n-----\n", StrChr(strChr, character));
}
*/
/*
Objective: Convert a string of numbers into a integer
Input: String of numbers as char*
Output: Returns vint varibale with the number
*/
/*
int AtoI (const char *strAtoI){
	int num=0, length=strlen(strAtoI), i=0;
	//if string entered is negative alter start point
	if (strAtoI[0] == '-')
		i = 1;
	//loop that runs entire length, transfers string to int
	for (; i<length; i++){
		num = num*10+ (strAtoI[i]-'0');
	}
	//if int was negative
	if (strAtoI[0] == '-')
		num *= -1;
	
	return num;
}
*/
/*
Objective: Compares two strings and returns value >, <, or = to 0
Input: Two strings are passed through as parameters
Output: Returns either <, >, or = to 0 depending on the comparison
*/
/*
int StrCmp (const char *str1Cmp, const char *str2Cmp){
	int *addr1 = str1Cmp, *addr2 = str2Cmp;
	//loop to run while not delimiter
	while (*addr1 != '\0'){
		if (*addr2 == '\0')
			return  1;
        if (*addr2 > *addr1)
			return -1;
        if (*addr2 < *addr1)
			return  1;
        addr1++;
        addr2++;
    }
    if (*addr2 != '\0')
		return -1;

    return 0;
}
*/
/*
Objective: Copies a source string onto a destination string
Input: Both a source and a destination string
Output: The final destination string
*/
/*
char *StrCpy (char *destination, const char *source){
	int length=strlen(source);
	for(int i=0; i<length; i++){
		destination[i] = source[i];
	}
	destination[length] = '\0';
	return destination;
}
*/
/*
Objective: Appends one string onto the end of another
Input: Both a source and a destination string
Output: The final destination string
*/
/*
char *StrCat(char *destinationCat, const char *sourceCat){
    int lengthD = strlen(destinationCat), lengthS = strlen(sourceCat);
    destinationCat[lengthD] = ' ';
	//loop that runs until the length of source
    for (int i=lengthD, j=0; j<lengthS; i++, j++) {
        destinationCat[i] = sourceCat[j];
    }
	int i=lengthD+lengthS;
    *(destinationCat+i) = NULL;
    return destinationCat;
}
/*
/*
Objective: Finds the first position of a character ad returns the following string
Input: A string and a character to search
Output: Returns the final remaining string 
*/
/*
char *StrChr(char *str, int character){
    int length = strlen(str);
    int flag = 0;
    //loop that runs length of string and searches for the character
    for (int i = 0; i <length; i++) {
        if (str[i]==character) {
            flag = i;
            break;
        }
    }
    return str+flag;
}
*/

//B

struct myWord {
	char Word[21];
	int Length;
};

int main(void){
	//create WordList of structure myWord
	struct myWord WordList[20];
	char myString[] = "the cat in the hat jumped over the lazy fox";
	char *token = strtok(myString, " ");
	int i=0, temp;
	//loop until there are no more words left
	while (token!=NULL){
		strcpy(WordList[i].Word, token);
		WordList[i].Length = strlen(token);
		token = strtok(NULL, " ");
		printf("%s, length %d\n", WordList[i].Word, WordList[i].Length);
		i++;
	}

	char *tempWord;
	//make a temp structure
	//bubble sort
	for (int j=0; j<i; j++){
		for (int k=1; k<=i; k++){
			//if previous word is less less than next word swap them and their length
			if (strcmp(WordList[k-1].Word, WordList[k].Word)>0){
				strcpy(tempWord, WordList[k-1].Word);
				strcpy(WordList[k-1].Word, WordList[k].Word);
				strcpy(WordList[k].Word, tempWord);
				temp = WordList[k-1].Length;
				WordList[k-1].Length = WordList[k].Length;
				WordList[k].Length = temp;
			}
		}
	}
	printf("\n");
	//loop that prints all words and lengths
	for (int j=0; j<i; j++){
		printf("%s, length %d\n", WordList[j].Word, WordList[j].Length);
	}
}






