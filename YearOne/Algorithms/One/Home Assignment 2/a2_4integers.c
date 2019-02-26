/*
Ryan Lebeau
24/10/2016
a2_integers.c
*/

#include <stdio.h>
int main(void)
{
	//creating the needed variables
	int num1, num2, num3, num4, largest, smallest;
	//taking the four inputed numbers and assigning them
	printf("Enter four integers with a space inbetween each: ");
	scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
	
	//checking if the first number is larger than the second
	if (num1 >= num2){
		//setting the first number as largest
		largest = num1;
		//setting the second number as smallest
		smallest = num2;
	}
	//if the second number is larger than the first
	else{
		//setting the second number as largest
		largest = num2;
		//setting the first number as smallest
		smallest = num1;
	}
	
	//checking if the third number is larger than the current largest number
	if (num3 >= largest){
		//reassigning the largest number as the third number
		largest = num3;
	}
	//if the third number is smaller than the current smallest number
	else if (num3 <= smallest){
		//reassigning the smallest number as the third number
		smallest = num3;
	}
	
	//checking if the fourth number is larger than the current largest number
	if (num4 >= largest){
		//reassigning the largest number as the fourth number
		largest = num4;
	}
	//if the fourth number is smaller than the current smallest number
	else if (num4 <= smallest){
		//reassiging the smallest number as the fourth number
		smallest = num4;
	}
	
	//displaying the largest and smallest numbers 
	printf("Largest: %i\nSmallest: %i", largest, smallest);
}