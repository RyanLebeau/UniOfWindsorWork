/*
Ryan Lebeau
12/03/2017
assign3.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function declarations
void letterAnalysis(int, char[][80]);
int wordLengthAnalysis(int, char[][80], int);
void wordAnalysis(int, char[][80]);

int main(void){
	int numLines, wordLengthNum;
	//stores number of lines into numLines
	scanf("%d\n", &numLines);
	//creates a dynamic array with rows to numLines
	char (*text)[80] = malloc(sizeof(char[numLines][80]));
	//scan every line of input until a '\n' and store in inidivual rows of 'text'
	for (int i=0; i<numLines; i++){
		scanf("%[^\n]\n", text[i]);
	}
	letterAnalysis(numLines, text);
	printf("------------\n");
	//loop that runs max number of characters in a word (20)
	for (int i=1; i<=20; i++){
		//call funciton and store returned word length in 'wordLengthNum'
		wordLengthNum = wordLengthAnalysis(numLines, text, i);
		//formatting output, if longer than 1 word print 'words'
		if (wordLengthNum==1)
			printf("%*d word of length %d\n", 3, wordLengthNum, i);
		else
			printf("%*d words of length %d\n", 3, wordLengthNum, i);
	}
	printf("------------\n");
	wordAnalysis(numLines, text);

}

/*
Objective: To find the number of times a letter occurs in the entire entered text
Input: The number of text lines and the 2D array with all text are parameters
Output: Prints the number of times a letter is repeated
*/
void letterAnalysis(int numLines, char(*text)[80]){
	//creating arrays to store which letter repeated
	int alphaCount[26] = {0};
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char length;
	//loop that runs for the amount of lines entered
	for (int i=0;i<numLines;i++){
		//loop that runs for the length of current line 
		for (int j=0;j<strlen(text[i]);j++){
			//takes current character and increases counter in alphaCount by 1
			switch(text[i][j]){
				case'A': case'a': alphaCount[0]+=1; break;
				case'B': case'b': alphaCount[1]+=1; break;
				case'C': case'c': alphaCount[2]+=1; break;
				case'D': case'd': alphaCount[3]+=1; break;
				case'E': case'e': alphaCount[4]+=1; break;
				case'F': case'f': alphaCount[5]+=1; break;
				case'G': case'g': alphaCount[6]+=1; break;
				case'H': case'h': alphaCount[7]+=1; break;
				case'I': case'i': alphaCount[8]+=1; break;
				case'J': case'j': alphaCount[9]+=1; break;
				case'K': case'k': alphaCount[10]+=1; break;
				case'L': case'l': alphaCount[11]+=1; break;
				case'M': case'm': alphaCount[12]+=1; break;
				case'N': case'n': alphaCount[13]+=1; break;
				case'O': case'o': alphaCount[14]+=1; break;
				case'P': case'p': alphaCount[15]+=1; break;
				case'Q': case'q': alphaCount[16]+=1; break;
				case'R': case'r': alphaCount[17]+=1; break;
				case'S': case's': alphaCount[18]+=1; break;
				case'T': case't': alphaCount[19]+=1; break;
				case'U': case'u': alphaCount[20]+=1; break;
				case'V': case'v': alphaCount[21]+=1; break;
				case'W': case'w': alphaCount[22]+=1; break;
				case'X': case'x': alphaCount[23]+=1; break;
				case'Y': case'y': alphaCount[24]+=1; break;
				case'Z': case'z': alphaCount[25]+=1; break;
				default: break;
			}
		}
	}
	printf("Total letter counts:\n");
	//loop that prints number of occurences for each alpha letter
	for (int i=0;i<26;i++){
		printf("%c: %*d\n", alphabet[i], 2, alphaCount[i]);
	}
}

/*
Objective: To find the number of words that are a certain length
Input: Number of lines entered, all text that was entered, and length to check are parameters
Output: Returns the number of words that have the entered length
*/
int wordLengthAnalysis(int numLines, char (*text)[80], int length){
	//set the delimiter for 'strtok'
	char delim[] = " ";
	//token for strtok
	char *word = " ";
	//copy of the original 2D array since strtok edits array
	char (*copyStr)[80] = malloc(sizeof(char[numLines][80]));
	int wordCounter=0, wordLength;
	
	//loop that runs for number of lines entered
	for (int i=0; i<numLines; i++){
		//sets current line 'copyStr' as a copy of the current line of 'text'
		strcpy(copyStr[i], text[i]);
		//set the first word as token
		word = strtok(text[i], delim);
		//while there are still words to find in row of 'text'
		while (word != NULL){
			wordLength = strlen(word);
			
			if (wordLength == length){
				wordCounter++;
			}
			//next word as new token
			word = strtok(NULL, delim);
		}
		//sets row of 'text' array back to the original
		strcpy(text[i], copyStr[i]);
	}
	return wordCounter;
}

/*
Objective: To find the number of times each word repeats and print them to the user 
Input: Number of lines entered and 2D array with all text 'text'
Output: Prints each word and how many times it has repeated (repeated words only print once)
*/
void wordAnalysis(int numLines, char (*text)[80]){
	//'wordCount' counts the current word total, 'repeatCount' counts how many times a word has repeated
	int wordCount = 1, repeatCount=0;
	//dynamic array with size wordCount that will store how many times a word has repeated 
	int *numRep = malloc(wordCount*sizeof(int));
	//dynamic 2d array that will be a copy of 'text'
	char (*copyStr)[80] = malloc(sizeof(char[numLines][80]));
	//dynamic 2d array that will store each individual word
	char (*words)[20] = malloc(sizeof(char[wordCount][20]));

	//for loop that runs for number of lines entered
	for(int i=0;i<numLines; i++){
		strcpy(copyStr[i], text[i]);
		//sets the first word as current token in 'word1'
		char *word1 = strtok(copyStr[i], " ");
		while(word1 != NULL){
			//adds current word to 'words' array
			strcpy(words[wordCount-1], word1);
			wordCount++;
			//sets new word as current token
			word1 = strtok(NULL, " ");
		}
		//since strtok would not return last word, strrchr will
		char *lastWord = strrchr(text[i], ' ');
		if (lastWord !=NULL){
			//removes the \n from each last word
			lastWord[strlen(lastWord) -1] = 0;
			//adds it to the 'words' array
			strcpy(words[wordCount-2], lastWord+1);
		}
	}
	
	//since calloc would not work, set each element of 'numRep' to zero
	for (int j=0; j<wordCount; j++){
		numRep[j] = 0;
	}
	
	//loop that runs for number of words
	for (int j=0; j<wordCount; j++){
		//loop that runs for number of words
		for (int k=0; k<wordCount; k++){
			//if current word j repeats within 'words' array
			if (!strcmp(words[j], words[k])){
				repeatCount += 1;
				//if the current word has already repeted set it to 'X' (used when printing)
				if (repeatCount>1){
					strcpy(words[k], "X");
				}
			}
		}
		//if current word j repeats store number of repetitions in 'numRep' at j
		if (repeatCount>1){
			numRep[j] = repeatCount;
		}
		else if (repeatCount==1){
			numRep[j] += repeatCount;
		}
		repeatCount = 0;
	}
	
	//loop thta runs for number of words
	for (int p=0; p<wordCount-1; p++){
		//if the word and repetition has already been printed do not print again
		if (!strcmp(words[p], "X"))
			continue;
		//if word has not yet been printed and repeats print "times"
		if (numRep[p] >1){
			printf("\"%-*s\" appeared %d times\n", 20, words[p], numRep[p]);
		//if word has not yet been printed and does not repeat print "time"
		}else{
			printf("\"%-*s\" appeared %d time\n", 20, words[p], numRep[p]);
		}
	}
}










