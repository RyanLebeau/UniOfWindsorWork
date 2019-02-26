/*
Ryan Lebeau
24/10/2016
a2_addfrac.c
*/

#include <stdio.h>
int main(void)
{
	//declaring the needed variables
	int num1, denom1, num2,denom2, result_num, result_denom;
	//prompting the user for the fractions input
	printf("Enter two fractions seperated by a plus sign: ");
	//storing each numerator and denominator in the respective variables
	scanf("%i/%i+%i/%i", &num1, &denom1, &num2, &denom2);
	//calculating the final numerator
	result_num = (num1*denom2) + (num2*denom1);
	//calculating the final denominator
	result_denom = denom1*denom2;
	//displaying the final sum
	printf("The sum is %i/%i.", result_num, result_denom);
}