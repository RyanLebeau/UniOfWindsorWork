/*
Ryan Lebeau
15/02/2017
Lab4.c
*/

/*
1
*salary = 200
salary1 = 20000
salary2 = 60000
salary3 = 2008
*/

/*
2

Objective: To find the largest element in an array
Input: Array to search and size of the array
Output: Returns the largest value through 'temp'
int *Largest(int *array, int size){
	int temp = *(array);
	for (int i=0; i<SIZE; i++){
		if (temp < *(array +i))
			temp = i;
	}
	return (array+temp);
}
*/

/*
3

Objective: Swaps two pointer's values
Input: Pointer as 'x' and pointer as 'y'
Output: The new values of x and y are changed, nothing is returned
void Swap(int*x, int*y){
	int temp = *x;
	*x = *y;
	*y = temp;
}
*/

//4
#include <stdio.h>
#define SIZE 10

//function declarations
int* Largest(int *, int);
void Swap(int*, int*);

int main(void){
	//declaring varibales and pointers for 'Swap'
	int x=5, y=1;
	
	//declaring and printing the array
	int array[SIZE] = {0,1,2,3,4,5,4,3,2,1};
	printf("The array is {%d", *(array));
	for (int i=1;i<SIZE;i++)
		printf(",%d", *(array+i));
	
	//pointer to the Largest function
	int *LargestVar;
	LargestVar = Largest(array, SIZE);
	//finishing the array print
	printf("} and the largest element is %d, the address is %d.", *LargestVar, Largest(array, SIZE));
	
	//printing the values and calling 'Swap'
	printf("\nPreSwap:\nx=%d, y=%d", x, y);
	Swap(&x, &y);
	printf("\nPostSwap:\nx=%d, y=%d", x, y);
	return 0;
}

/*
Objective: To find the largest element in an array
Input: Array to search and size of the array
Output: Returns the largest value through 'temp'
*/
int *Largest(int *array, int size){
	int temp = *(array);
	//loop to run through each element and check if larger than current largest
	for (int i=0; i<SIZE; i++){
		if (temp < *(array +i))
			temp = i;
	}
	return (array+temp);
}

/*
Objective: Swaps two pointer's values
Input: Pointer as 'x' and pointer as 'y'
Output: The new values of x and y are changed, nothing is returned
*/
void Swap(int*x, int*y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

