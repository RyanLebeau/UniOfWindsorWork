/*
Ryan Lebeau
19/11/2016
question2.c
*/

#include <stdio.h>
#include <string.h>
int main(void)
{
	//declaring the needed variables
	int num1, denom1, num2,denom2, result_num, result_denom;
	char op;
	char op_name[] = "";

	
	//prompting the user for the fractions input
	printf("Enter two fractions seperated by an operator: ");
	//storing each numerator, denominator, and operator in the respective variables
	scanf("%i/%i%c%i/%i", &num1, &denom1, &op, &num2, &denom2);
	
	//switch case to determine which operator was entered
	switch (op){
		//if addiiton
		case '+':
			//calculating the final numerator
			result_num = (num1*denom2) + (num2*denom1);
			//calculating the final denominator
			result_denom = denom1*denom2;
			//setting the name of the product created
			strcpy(op_name, "sum");
			break;
		//if subtraction
		case '-':
			result_num = (num1*denom2) - (num2*denom1);
			result_denom = denom1*denom2;
			strcpy(op_name, "difference");
			break;
		//if multiplication
		case '*':
			result_num = num1*num2;
			result_denom = denom1*denom2;
			strcpy(op_name, "product");
			break;
		//if division
		case '/':
			result_num = num1*denom2;
			result_denom = denom1*num2;
			strcpy(op_name, "quotient");
			break;
		//if an invalid operator is entered end the program
		default:
			printf("Invalid operator, please use * + - /");
			return 0;
	}
	
	//displaying the final value
	printf("The %s is %i/%i.", op_name, result_num, result_denom);
}