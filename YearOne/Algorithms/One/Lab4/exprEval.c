/*
Ryan Lebeau
DATE
exprEval.c
*/

#include <stdio.h>
int main(void)
{
	//creating the variables to store entered inputs
	float num1, num2;
	char op;
	//prompting the user for two numbers and an operator
	printf("Enter a simple expression with no spaces: ");
	//storing the numbers and operator in their respective variable
	scanf("%f%c%f", &num1, &op, &num2);
	
	//if the entered operator was addition
	if (op == '+'){
		//returns the original expression and the sum
		printf("Output: %.2f + %.2f = %.2f", num1, num2, num1+num2);
	}
	//if the entered operator was subtraction
	else if (op == '-'){
		//returns the original expression and the difference
		printf("Output: %.2f - %.2f = %.2f", num1, num2, num1-num2);
	}
	//if the entered operator was multiplication
	else if (op == '*'){
		//returns the original expression and the product
		printf("Output: %.2f * %.2f = %.2f", num1, num2, num1*num2);
	}
	//if the entered operator was division
	else if (op == '/'){
		//if the user attempts to divide by zero
		if (num2 == 0){
			//informs the user you can not divide by zero
			printf("Output: Can not divide by zero!");
		}
		//if the second number is not zero
		else{
			//returns the original expression and the quotient
			printf("Output: %.2f / %.2f = %.2f", num1, num2, num1/num2);
		}
	}
	//if the entered operator is not +, -, *, or /
	else{
		printf("Output: Unknown operator!");
	}
}