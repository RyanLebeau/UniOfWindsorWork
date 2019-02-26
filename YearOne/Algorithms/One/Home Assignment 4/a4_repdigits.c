/*
Ryan Lebeau
19/11/2016
a4_repdigits.c
*/

#include <stdio.h>
#include <stdbool.h>
int main(void)
{
	//digit_seen array keeps track of which digits have already been entered
	bool digit_seen[10] = {false};
	//rep_digit stores if the current number has a repeating digit
	bool rep_digit = false;
	//counter variables for loops and digit stores the current digit
	int j, digit, temp_num=1, test_num=0;
	
	//this loop checks each entered number for repeating digits
	while (temp_num > 0){
		//resetting the value of 'test_num'
		test_num = 0;
		//prompting the user for a number
		printf("Enter an integer to be checked for repeating digits (stop with 0): ");
		//saving this number in 'temp_num'
		scanf("%d", &temp_num);
		//setting 'test_num' to 'temp_num' so the number can be changed
		test_num = temp_num;
		
		//set the value of j to zero for use in the for loop
		j = 0;
		//resets every digit that has been seen to false, in preperation for the next number
		for (; j<=9; j++){
			digit_seen[j] = false;
		}
		
		//checks current number for repeating digits
		while(test_num>=1){
			//stores the last digit of the current number in 'digit'
			digit = test_num%10;
			//if a digit is repeated
			if (digit_seen[digit]){
				//exit this current while loop
				test_num = 0;
				//save that a digit has been repeated
				rep_digit = true;
			}
			//if the current digit is not a repeat
			else{
				//save that this digit has been seen by changing its value in digit_seen to true
				digit_seen[digit] = true;
				//divide by ten to move onto the next digit in the number
				test_num /= 10;
			}
		}
		
		//if a digit was repeated in the number
		if (rep_digit){
			//reset the variable in preperation of the next number
			rep_digit = false;
			//tell the user the number and that it repeated a digit
			printf("%d has a repeated digit(s).\n", temp_num);
			//formatting the output
			printf("--------\n");
		}
		//if a digit was not repeated
		else if (!rep_digit && temp_num != 0){
			//tell the user the number it and that it did not repeat a digit
			printf("%d has no repeated digits.\n", temp_num);
			//formatting the output
			printf("--------\n");
		}
	}
	
}