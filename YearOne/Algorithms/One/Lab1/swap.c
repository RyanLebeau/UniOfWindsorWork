#include <stdio.h>
int main(void)
{
	int num1, num2, temp;
	printf("Enter the first number: ");
	scanf("%d", &num1);
	printf("Enter the second number: ");
	scanf("%d", &num2);
	temp = num1;
	num1 = num2;
	num2 = temp;
	printf("Before swapping, the first number was %i and the second number was %i.\nAfter swapping, the first number is %i and the second number is %i.", temp, num1, num1, num2);
	return 0;
}