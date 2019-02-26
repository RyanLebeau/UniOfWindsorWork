/*
Ryan Lebeau
08/11/2016
pinCode.c
*/

#include <stdio.h>
int main(void)
{
	//declaring all the needed variables
	int i, k, counterDiv, entCode0, entCode1, entDigits[5], j=0;
	//for loop to keep track of the 6 attempts
	for (i=1; i<7; i++){
		//asking the user for a code
		printf("Enter pin code (Attempt %d): ", i);
		scanf("%d", &entCode0);
		//storing the entered code in another variable so it can be used later
		entCode1 = entCode0;
		//if the entered code is 5 digits
		if (entCode1<=99999 && entCode1>=10000){
			//seperating the code into each digits
			while(j<5){
				entDigits[j] = entCode0%10;
				entCode0 /= 10;
				++j;
			}
			//for loop to run through each digit
			for (k=0; k<5; k++){
				//making sure the digit isnt zero
				if (entDigits[k] != 0){
					entDigits[k] = entDigits[k] % 3;
					//if the number is divisble by 3 add one to a counter
					if (entDigits[k] == 0){
						++counterDiv;
					}
				}
			}
			/*If the counter is 5 the code is correct,
			since the only way the counter can reach 5
			is that each digit had to have been divisible
			by 3. If it wasn't, the counter would be less 
			than 5.*/
			if (counterDiv == 5){
				printf("Code %d is valid!", entCode1);
				return 0;
			}
			//if the counter is less than 5
			else{
				printf("Code %d is invalid!\n", entCode1);
			}
		}
		//if the code is less than or more than 5 digits
		else{
			printf("Code %d is invalid!\n", entCode1);
		}
		//ressetting the needed variables for a new code
		j=0;
		counterDiv = 0;
	}
	//after 6 codes entered wrong this line wil print
	printf("Intruder Alert!");
}