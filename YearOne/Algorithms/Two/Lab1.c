/*
Ryan Lebeau
18/01/2017
Lab1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//declarations for each function
int summation(int);
int factorial(int);
int fibonacci(int);
int gcd(int, int);
int power(float, float);

//the main function which controls all user inputs and calling of other functions, returns zero and takes no parameters
int main(void){
	//required variables
	int choiceSel, enteredNum, enteredNum2;
	float base, power1;
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
			summation(enteredNum);
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
			factorial(enteredNum);
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
			fibonacci(enteredNum);
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
			gcd(enteredNum, enteredNum2);
			break;
		//prompts the user for a valid number and launches 'power' function
		case 5:
			printf("Please enter a base followed by a power (base>0, power >=0): ");
			scanf("%f %f", &base, &power1);
			//if the user enters an invalid number
			while(base<1 || power1<0){
				printf("\nInvalid number(s). Please enter a base followed by a power (base>0, power >=0): ");
				scanf("%f %f", &base, &power1);
			}
			power(base, power1);
			break;
		//if an invalid number was entered
		default:
			printf("\nThat is not an option.");
			break;
	}
}

//Takes the entered number by the user as a parameter and adds each previous decreasing term and outputs zero
int summation(int n){
	printf("\nThe summation of %d is %d", n, n*(n+1)/2);
	return 0;
}

/*Takes the entered number in from the user and 
it trough a loop which multiplies the original by
each previous term, returning zero*/
int factorial(int n1){
	int n2, fact=1;
	n2 = n1;
	//decreases entered number
	for (;n1>0;n1--){
		fact *= n1;
	}
	printf("\nThe factorial of %d is %d", n2, fact);
	return 0;
}

//Takes the entered number as a parameter and searches for the fibonacci number
int fibonacci(int n){
	int test1=0, test2=0, fib=0;
	//array at size of a variable, storing in heap storage
	int *fibSeries = malloc(n*sizeof(int));
	//creates fibonacci series into an array to the limit of n
	for (int i=1;n>=i;i++){
		if (i==1 || i==2){
			fibSeries[0] = 1;
			fibSeries[1] = 1;
		}
		else
			fibSeries[i-1] = fibSeries[i-2]+fibSeries[i-3];
	}
	printf("\nThe fibonacci number from %d is %d", n, fibSeries[n-1]);
	return 0;
}

//Takes two parameters and finds the greatest common denominator, returning zero
int gcd(int x, int y){
	int yTemp, remainder, rem2, temp;
	//makes x the largest number of the two entered
	if (y>x){
		temp=x;
		x=y;
		y=temp;
	}
	yTemp = y;
	remainder = x%y;
	//uses a euclidean algorithm to produce the greatest common factor
	while (remainder>0){
		rem2=y%remainder;
		y = remainder;
		remainder = rem2;
	}
	printf("\nThe GCD between (%d,%d) is %d", x, yTemp, y);
	return 0;
}

//Takes two parameters and uses the math pow() to find the power, returns zero
int power(float base, float power){
	int result=1;
	for (;power>0;power--){
		result *= base;
	}
	printf("\nThe value is %d", result);
	return 0;
}




