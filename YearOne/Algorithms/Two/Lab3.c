/*
Ryan Lebeau
01/02/2017
Lab3.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define M 6
#define N 5

//function declarations
int populateRandom2D(int[][N], int(*)[N]);
int printArray2D(int[][N]);
bool linearSearch2D(int[][N], int);
int leftShift2D(int[][N], int(*)[N]);

//main function which controls user inputs and function calls
int main(void){
	int a2D [M][N] = {0}, (*a2Dptr)[N] = a2D, userChoice, searchNum;
	bool done = false, search;
	srand(time(NULL));
	//repeat prompts until exited
	while (!done){
		printf("Fill the array - 1\n"
				"Search the array - 2\n"
				"Left shift the array - 3\n"
				"Print the array - 4\n"
				"Exit - 0\n"
				"Please enter a choice: ");
		scanf("%d", &userChoice);
		//decides which case to run based off of user entered number
		switch(userChoice){
			case 1:
				populateRandom2D(a2D, a2Dptr); break;
			case 2:
				printf("Enter a value to search for: ");
				scanf("%d", &searchNum);
				search = linearSearch2D(a2D, searchNum);
				if (search)
					printf("%d is within the list.\n", searchNum);
				else
					printf("%d is not within the list.\n", searchNum);
				break;
			case 3:
				leftShift2D(a2D, a2Dptr); break;
			case 4:
				printArray2D(a2D); break;
			case 0:
				done = true; break;
			default:
				printf("That was not a valid option.\n"); break;
		}
		printf("\n");
	}
	return 0;
}


/*
Objective: fills the array with random numbers from 1-M*N, non repeating numbers
Input: takes 2D array and pointer to the array as parameters
Output: ouputs values of list through pointer, returns 0
*/
int populateRandom2D(int a2D[M][N], int(*a2Dptr)[N]){
	int tempVal;
	//cycle through each value in array
	for (int i=0; i < M; i++){
		for (int j=0; j<N; j++){
			tempVal = rand() % (M*N) +1;
			//if the number generated already exists in the list generte new number
			while(linearSearch2D(a2D, tempVal)){
				tempVal = rand() % (M*N) +1;
			}
			*(a2Dptr[i] + j) = tempVal;
		}
	} 
	return 0;
}

/*
Objective: display the array to the user formatted into columns
Input: takes the 2D array as a parameter
Output: prints the array and returns 0
*/
int printArray2D(int a2D[M][N]){
	for (int i=0; i < M; i++){
		for (int j=0; j<N; j++){
			printf("%*d", 4, a2D[i][j]);
		}
		printf("\n");
	} 
	return 0;
}


/*
Objective: shifts every value in the array left by one, leading numbers are last of previous row
Input: takes the 2D array and a pointer to that array as parameters
Output: sets new values for array through pointers and returns 0
*/
int leftShift2D(int a2D[M][N], int (*a2Dptr)[N]){
	int firstNum, temp;
	for (int i=0; i<M; i++){
		for (int j=0; j<N; j++){
			//if it is the first value save it before it is replaced
			if (i==0 && j ==0){
				firstNum = *(a2Dptr[i] + j);
			}
			//if the first number in the row set it as previous row last term
			else if(j == 0){
				*(a2Dptr[i-1] + N-1) = *(a2Dptr[i] + j);
			}
			//if last term in the array move value left and set as first
			else if(i== M-1 && j== N-1){
				*(a2Dptr[i] + j-1) = *(a2Dptr[i] + j);
				*(a2Dptr[i] + j) = firstNum;
			}
			//moves values left through the rows
			else{
				*(a2Dptr[i] + j-1) = *(a2Dptr[i] + j);
			}
		}
	}
	return 0;
}

/*
Objective: checks if a number is found within the array
Input: takes 2D array and the value to be searched for as parameters
Output: returns true or false based on if the number was found or not
*/
bool linearSearch2D(int a2D[M][N], int value){
	for (int i=0; i < M; i++){
		for (int j=0; j<N; j++){
			//if the number we are searching for is the current term
			if (value == a2D[i][j]){
				return true;
			}
		}
	}
	return false;
}