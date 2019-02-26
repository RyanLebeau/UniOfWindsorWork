/*
Ryan Lebeau
02/12/2016
a5_gcd_recursive.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int gcd(int,int);

int main(void)
{
	//initiating needed variables
	int m,n,temp;
	//setting the seed for random as time
	srand(time(NULL));
	//setting m and n as radnom variables from 2-100
	//m = rand()%99 + 2;
	//n = rand()%99 + 2;
	m=99;
	n=10;
	//makes sure m is always the larger of the two numbers
	if (m<n){
		temp = m;
		m = n;
		n = temp;
	}
	//returns the GCD by calling the function
	printf("The GCD of %d and %d is %d.", m, n, gcd(m,n));
	
}

//finding the GCD between the two random numbers
int gcd(int m, int n)
{
	//checks if m%n isn't equal to zero
	if(m%n != 0){
		/*sets the final value of n as the remainder for the
		final recursive step, which is the gcd*/
		n = gcd(n,m%n);
	}
	//returning the gcd
	return n;
}