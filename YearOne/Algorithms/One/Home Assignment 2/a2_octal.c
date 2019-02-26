/*
Ryan Lebeau
24/10/2016
a2_octal.c
*/

#include <stdio.h>
int main(void)
{
	//creating the variable
	int num1;
	//prompting the user for a number between the parameters
	printf("Enter a number between 0 and 32767: ");
	//storing the number in num1
	scanf("%d", &num1);
	//returning the number in octal padded left with 0's
	printf("%05o", num1);
}