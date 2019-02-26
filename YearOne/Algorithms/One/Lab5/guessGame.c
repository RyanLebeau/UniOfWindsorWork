/*
Ryan Lebeau
DATE
exprEval.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int main(void)
{
	//to get a true random number between 1-50
	srand (time(NULL));
	int goal = rand() % 50 + 1;
	int guessNum, guessCounter;
	//creating a boolean variable for the while loop
	bool loopCont = true;
	
	//while loop to continuously ask the user
	while (loopCont == true){
		//asking the user for a number
		printf("Enter your guess (between 1 and 50): ");
		//storing that number in the variable 'guessNum'
		scanf("%d", &guessNum);
		//if the guessed number is correct
		if (guessNum == goal){
			//informing the user they are correct
			printf("Correct, the number was %d.", goal);
			//concelling the loop since the user was correct
			loopCont = false;
		}
		//if the guessed number is greater than the goal
		else if (guessNum > goal){
			//informing the user the guess was too high
			printf("Too high...\n");
			//keeping track of the number of guesses
			++ guessCounter;
		}
		//if the guessed number is less than the goal
		else if (guessNum < goal){
			//informing the user the guess was too low
			printf("Too low...\n");
			//keeping track of the numbe rof guesses
			++ guessCounter;
		}
		//if ten guess have been completed
		if (guessCounter == 10){
			//tell the user what the random number was
			printf("Sorry, the number was %d.", goal);
			//cancelling the loop since the user ran out of guesses
			loopCont = false;
		}
	}
}