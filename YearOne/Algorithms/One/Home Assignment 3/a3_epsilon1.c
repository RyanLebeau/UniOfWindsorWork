/*
Ryan Lebeau
04/11/2016
a3_epsilon1.c
*/

#include <stdio.h>
int main(void)
{
	//declaring the needed variables
	float eps=0.0;
	float epsilon;
	float term = 1.0;
	float i = 1, fact = 1;
	//prompting the user for a value of epsilon
	printf("Enter a small float value for epsilon: ");
	scanf("%f", &epsilon);
	
	//loop to find the approximaiton of e
	while (term>=epsilon){
		//adding 'term' to epsilon
		eps = eps+term;
		//multiplying the 'fact' variable by 'i'
		fact *= i;
		//adding one to 'i' 
		++i;
		//solving for term by dividing 'i' by 'fact'
		term = 1/fact;
	}
	
	//returning the approximaiton of e to the user
	printf("Approximation of e: %f ", eps);
}