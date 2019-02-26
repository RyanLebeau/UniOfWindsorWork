/*
Ryan Lebeau
04/11/2016
question2.c
*/

#include <stdio.h>
int main(void)
{
	//creating the needed variables
	int num1, num2;
	//prompting the user for a two-digit number
	printf("Enter a two-digit number: ");
	//storing each digit in their own variable
	scanf("%1d%1d", &num1, &num2);
	
	//printing the statement before the switch statements are run
	printf("You entered the number ");
	
	//if the first digit is a 1 
	if (num1 == 1){
		/*check the value of the second digit so the 
		corresponding special name can be used. For example, 
		if the first digit is one this switch statement will
		be run and if the second is two, then the name
		is twelve*/
		switch (num2){
			case 0:
				printf("ten.");
				break;
			case 1:
				printf("eleven.");
				break;
			case 2:
				printf("twelve.");
				break;
			case 3:
				printf("thirteen.");
				break;
			case 4:
				printf("fourteen.");
				break;
			case 5:
				printf("fifteen.");
				break;
			case 6:
				printf("sixteen.");
				break;
			case 7:
				printf("seventeen.");
				break;
			case 8:
				printf("eighteen.");
				break;
			case 9:
				printf("nineteen.");
				break;
		}
	}
	
	//if the first digit is not a one
	else{
		/* check what the first digit is and display
		the correct corresponding word. For example, 
		if the first digit is a 4 then the switch 
		statement will display "four"*/
		switch (num1){
			case 2:
				printf("twenty");
				break;
			case 3:
				printf("thirty");
				break;
			case 4:
				printf("forty");
				break;
			case 5:
				printf("fiddy");
				break;
			case 6:
				printf("sixty");
				break;
			case 7:
				printf("seventy");
				break;
			case 8:
				printf("eighty");
				break;
			case 9:
				printf("ninety");
				break;
		}
		
		/*check the value of the second digit and
		display the corresponding word preceded with
		a hyphen. For example, if the second digit
		was a 5 then the switch statement would return
		"-five"*/
		switch (num2){
			case 1:
				printf("-one.");
				break;
			case 2:
				printf("-two.");
				break;
			case 3:
				printf("-three.");
				break;
			case 4:
				printf("-four.");
				break;
			case 5:
				printf("-five.");
				break;
			case 6:
				printf("-six.");
				break;
			case 7:
				printf("-seven.");
				break;
			case 8:
				printf("-eight.");
				break;
			case 9:
				printf("-nine.");
				break;
		}
	}
}








