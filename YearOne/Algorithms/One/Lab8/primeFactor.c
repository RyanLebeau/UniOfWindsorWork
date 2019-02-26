/*
Ryan Lebeau
21/11/2016
primeFactor.c
*/

#include <stdio.h>
#include <stdbool.h>
//defining functions
int readNum();
bool IsPrime(int);
int findPrimeCount(int, int);

int main(void)
{
	//defining p_flag to keep track if a number is prime
	bool p_flag = false;
	//creating num to store user number, and prime to store prime number
	int num, prime = 1;
	//calling the function readNum
	num = readNum();
	int num2;
	//starting the output format
	printf("%d = 1 ", num);
	//while num is not 1
	while (num!=1){
		//reset value of p_flag to false
		p_flag = false;
		//while p_flag is false
		while (!p_flag){
			//increase the number to check for prime
			prime++;
			//check if 'prime' is a prime number
			p_flag = IsPrime(prime);
		}
		num2 = num;
		//the value of num after a prime has been used on it
		num = findPrimeCount(num2, prime);
	}
	return 0;
}

//counts how many times a prime number is found within the user num
int findPrimeCount(int num, int prime)
{
	//creating the frequency variable
	int freq = 0;
	//check if num is divisble by prime 
	while (num%prime == 0){
		//add one to frequency
		freq++;
		//divide the original number by prime
		num /=prime;
	}
	//if the prime does dvide the number
	if (freq != 0)
		//print the format needed
		printf("x (%d^%d) ", prime, freq);
	//return the updated number to the current function
	return num;
}

//check if a number is prime
bool IsPrime(int prime)
{
	//creating i and p_flag
	int i = 2;
	bool p_flag = true;
	float check = 0;
	//checks to see if prime is actually prime, stops before 
	while (i<prime){
		check  = prime%i;
		//stops the loop when a number is found to not be prime
		if (check == 0){
			p_flag = false;
			i = prime;
		}
		else{
			i++;
		}
	}
	//return if the number is prime or not
	return p_flag;
}

//recieving a number from the user
int readNum(void)
{
	//boolean to track if the users number is allowed
	bool validNum = false;
	int num = 0;
	//while the user hasnt entered a true number
	while (!validNum){
		//ask and store in num
		printf("Enter a valid number (>1): ");
		scanf("%d", &num);
		//if the number is not greater than 1
		if (num <= 1){
			printf("Invalid Number.\n");
		}
		//if the number is greater than 1
		else if (num>1){
			validNum = true;
		}
	}
	//return the entered number
	return num;
	
	/*
	int num;
	printf("Enter a number(>1)");
	scanf("%d", &num);
	if (num<=1)
	{
		printf("Invalid number");
		num = readNum();
	}
	return num;
	*/
}