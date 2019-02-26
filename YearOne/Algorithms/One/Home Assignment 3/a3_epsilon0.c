/*
Ryan Lebeau
04/11/2016
a3_epsilon0.c
*/

#include <stdio.h>
int main(void)
{
	//creating the needed variables
	double epsilon=1, x=1, factorial=1;
	int limit, y;
	//prompting the user for a limit to epsilon
	printf("Enter a number to limit epsilon: ");
	//storing the input under 'limit'
	scanf("%d", &limit);
	
	//loop to calculate epsilon while 'x' is les than or equal to the limit
	while (x<=limit){
		//resetting the value of 'y' to calculate the factorial
		y = x;
		//calculating the factorial while above 0, as to not cancel the value
		while (y>0){
			//multiplying each value of 'y' by itself decreasing by one (factorial)
			factorial *= y;
			//subtracting one from 'y' to continue calculating the factorial
			--y;
		}
		//adding one divided by its factorial
		epsilon += 1/factorial;
		//resetting the value of factorial
		factorial = 1;
		//adding one to 'x' so the limit will eventually be reached
		++x;
	}
	
	//returning the value of epsilon to the user
	printf("The value of epsilon to the entered limit is %f", epsilon);
}