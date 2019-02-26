/*
Ryan Lebeau
01/02/2017
Lab2.c
*/

#include <stdio.h>
#include <stdlib.h>

int summation(int, int);
int factorial(int, int);
int fibonacci(int);
int gcd(int, int);
int power(int, int, int);

//the main function which controls all user inputs and calling of other functions, returns zero and takes no parameters
int main(void){
	//required variables
	int choiceSel, enteredNum, enteredNum2, base, power1, total, result;
	//prompting the user for an entered number
	printf("Summation -- 1\nFactorial -- 2\nFibonacci -- 3\nGCD -- 4\nPower -- 5\nExit -- 0\n");
	printf("Please enter a number choice: ");
	scanf("%d", &choiceSel);
	//decides which function to execute depending on which number was entered by the user
	switch(choiceSel){
		//if the user exited
		case 0:
			return 0;
		//prompts the user for a valid number and launches 'summation' function
		case 1:
			printf("Please enter a number (>0): ");
			scanf("%d", &enteredNum);
			//if the user enters an invalid number
			while(enteredNum<1){
				printf("\nInvalid number. Please enter a number (>0): ");
				scanf("%d", &enteredNum);
			}
			result = 0;
			result = summation(enteredNum, result);
			printf("The summation of %d is %d", enteredNum, result);
			break;
		//prompts the user for a valid number and launches 'factorial' function
		case 2:
			printf("Please enter a number (>0): ");
			scanf("%d", &enteredNum);
			//if the user enters an invalid number
			while(enteredNum<1){
				printf("\nInvalid number. Please enter a number (>0): ");
				scanf("%d", &enteredNum);
			}
			result = 1;
			result = factorial(enteredNum, result);
			printf("\nThe factorial of %d is %d", enteredNum, result);
			break;
		//prompts the user for a valid number and launches 'fibonacci' function
		case 3:
			printf("Please enter a number (>0): ");
			scanf("%d", &enteredNum);
			//if the user enters an invalid number
			while(enteredNum<1){
				printf("\nInvalid number. Please enter a number (>0): ");
				scanf("%d", &enteredNum);
			}
			result = fibonacci(enteredNum);
			printf("\nThe fibonacci number from %d is %d", enteredNum, result);
			break;
		//prompts the user for a valid number and launches 'gcd' function
		case 4:
			printf("Please enter two numbers seperated by a space (>0): ");
			scanf("%d %d", &enteredNum, &enteredNum2);
			//if the user enters an invalid number
			while(enteredNum<1 || enteredNum2<1){
				printf("\nInvalid number(s). Please enter two numbers seperated by a space (>0): ");
				scanf("%d %d", &enteredNum, &enteredNum2);
			}
			result = gcd(enteredNum, enteredNum2);
			printf("\nThe GCD between (%d,%d) is %d", enteredNum, enteredNum2, result);
			break;
		//prompts the user for a valid number and launches 'power' function
		case 5:
			printf("Please enter a base followed by a power (base>0, power >=0): ");
			scanf("%d %d", &base, &power1);
			//if the user enters an invalid number
			while(base<1 || power1<0){
				printf("\nInvalid number(s). Please enter a base followed by a power (base>0, power >=0): ");
				scanf("%d %d", &base, &power1);
			}
			result = 1;
			result = power(base, power1, result);
			printf("The result is %d", result);
			break;
		//if an invalid number was entered
		default:
			printf("\nThat is not an option.");
			break;
	}
}

//This function adds al previous terms of a number together passing through two variables
int summation(int enteredNum, int result){
	result += enteredNum;
	//as long as the number is not zero continue to run
	if (enteredNum>1){
		summation(--enteredNum, result);
	} else{
		return result;
	}
}

//This function multiplies a number by each previous term passing through two variables
int factorial(int enteredNum, int result){
	result *= enteredNum;
	//as long as the number is not zero continue
	if (enteredNum>1){
		factorial(--enteredNum, result);
	} else{
		return result;
	}
}

//This function creates the fibonnaci series uo until the entered number and returns that number
int fibonacci(int enteredNum){
	if (enteredNum == 1 || enteredNum == 2){
		return 1;
	} 
	return fibonacci(enteredNum-1)+fibonacci(enteredNum-2);
}

//This function checks the gcd between two numbers
int gcd(int entNum1, int entNum2){
	if(entNum1%entNum2 != 0){
		entNum2 = gcd(entNum2, entNum1%entNum2);
	}
	return entNum2;
}

//This function takes two numbers and finds the power value of them
int power(int base, int pow, int result){
	result *= base;
	//continues until pwer is at zero
	if (pow>1){
		power(base, --pow, result);
	} else{
		return result;
	}
}









