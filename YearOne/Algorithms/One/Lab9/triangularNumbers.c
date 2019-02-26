/*
Ryan Lebeau
29/11/2016
triangularNumbers.c
*/

#include <stdio.h>
//function declarations
int readNum(void);
int iterativeTriNum(int);
int recursiveTriNum(int);

int main(void)
{
	//storing the user entered number in 'number'
	int number = readNum();
	//outputting the iterative triangular number
	printf("Iterative: Triangular number of %d is %d.\n",
								number, iterativeTriNum(number));
	//outputting the recursive triangular number
	printf("Recursive: Triangular number of %d is %d.", 
								number, recursiveTriNum(number));
	
}

//getting a user inputted number
int readNum()
{
	int number;
	//prompting the user
	printf("Enter a valid number (>0): ");
	scanf("%d", &number);
	//if the number is invalid
	if (number<=0){
		//inform user
		printf("Invalid Number.\n");
		//prompt for another number
		number = readNum();
	}
	//returning number back to main
	return number;
}

//calculating the triangular number through iterations
int iterativeTriNum(int number)
{
	//creating triCount as a local variable
	int triCount=0;
	//adds each number from 0 to 'number' to 'triCount'
	for (int i=0; i<=number; i++)
		triCount += i;
	//return triCount back to main
	return triCount;
}

//defining triCount as a global variable
int triCount2=0;
//calculating the triangular number through recursion
int recursiveTriNum(int number)
{
	//adding 'number' to tricount then decreasing 'number' by 1
	triCount2 = triCount2+number--;
	//continue the recursion until 'number' is zero
	if(number>0)
		//call the function again using the updated 'number' as a parameter
		recursiveTriNum(number);
	//returning tricount back to main
	return triCount2;
}