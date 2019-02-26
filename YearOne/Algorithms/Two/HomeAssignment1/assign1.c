/*
Ryan Lebeau
29/01/2017
assign1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//function declarations
int find_prime_count(int, int, int *);
int find_next_prime(int, int, bool *);
bool is_prime(int);

/*
Objective: Main program function, handles openening of inputs and calls functions
Input: None
Output: Prints the input number in proper structure returns 0
*/
int main (void){
	int userNum = 1, primeCur = 2, *pairNumPtr, pairNum = 0;
	bool *donePtr, done = false;
	pairNumPtr = &pairNum;
	donePtr = &done;
	FILE *input = fopen("input.txt", "r+");
	//loop gathering inputs and outputs until input read is 0
	while (userNum != 0){
		fscanf(input, "%d \n", &userNum);
		//formats and prints the input number
		if (userNum != 0){
			printf("%*d!", 3, userNum);
			printf("  =  ");
		}
		//calls functions to determine answer
		while (!done){
			find_prime_count(primeCur, userNum, &pairNum);
			primeCur = find_next_prime(primeCur, userNum, &done);
		}
		//ressetting needed variable values for next input
		*donePtr = false;
		*pairNumPtr = 0;
		primeCur = 2;
		if (userNum != 0)
			printf("\n\n");
	}
	fclose(input);
	return 0;
}

/*
Objective: Count how many times a prime is within numbers leading up to input
Input: Current prime number, inputted number, and pointer counting the number of prints
Output: Prints the final answers and returns 0
*/
int find_prime_count(int primeCur, int userNum, int *pairNumPtr){
	int repCount=0, tempi;
	bool ifPrime = true;
	//to pass through every number up until the input number
	for (int i = 2;i<=userNum;i++){
		ifPrime = is_prime(i);
		//if the number is prime and is the current prime add one to rep counter
		if (ifPrime){
			if(i==primeCur)
				repCount++;
		}
		tempi = i;
		//if not prime then check how many time the current prime is within
		while(!ifPrime){
			if (i%primeCur==0){
				repCount++;
				i /= primeCur;
			}
			else{
				ifPrime = true;
				i = tempi;
			}
		}
	}
	//printing the prime and counter value in proper format
	if (*pairNumPtr == 9){
		printf("\n	");
		*pairNumPtr = 0;
	}
	if (repCount != 0 && primeCur == 2){
		printf("(%d^%d)", primeCur, repCount);
		*pairNumPtr += 1;
	}
	else if (repCount != 0){
		printf("*(%d^%d)", primeCur, repCount);
		*pairNumPtr += 1;
	}
	return 0;
}

/*
Objective: Finds the next prime value to use based off the previous prime value
Input: Prime that program was on, inputted number, and boolean if input number is done
Output: Returns the next prime value which is then used in find_prime_count 
*/
int find_next_prime(int primePrev, int userNum, bool *donePtr){
	int primeNew=0;
	bool ifPrime = false;
	primeNew = ++primePrev;
	if (primeNew > userNum){
		*donePtr = true;
	}
	//finding the next prime number, if there are none then change 'done' value
	while (!ifPrime){
		ifPrime = is_prime(primeNew);
		if (!ifPrime){
			primeNew = ++primePrev;
			if (primeNew > userNum){
				*donePtr = true;
				return 0;
			}
		}
		else
			ifPrime = true;
	}
	return primeNew;
}

/*
Objective: Check whether an inputted number is prime or not
Input: Number that will be checked
Output: True or false value whether number is prime
*/
bool is_prime(int i){
	int count=2, check;
	//checking to make sure no numbers are evenly divisible
	while (count<i){
		check = i%count;
		//if there are then returns false
		if(check == 0){
			return false;
		}
		else
			count++;
	}
	//if not then returns true
	return true;
}







