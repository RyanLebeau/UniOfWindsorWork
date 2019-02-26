/*
Ryan Lebeau
22/02/2017
Lab5.c
*/

/*
A

#include <stdio.h>
int main()
{
	//declare variable 'a' as value of 7
	int a = 7 ;
	
	//creates a pointer called 'aPtr'
	int *aPtr ;
	
	//aPtr now pints to variable 'a'
	aPtr = &a ;
	
	//prints the address to 'a'
	printf( "%p", &a );
	
	//prints the address 'aPtr' points towards
	printf( "%p", aPtr );
	
	//prints the address of the pointer 'aPtr'
	printf( "%p", &aPtr );
	
	//prints value of 'a': 7
	printf( "%d", a );
	
	//prints value of 'aPtr': 7
	printf( "%d", *aPtr );
	
	//prints address of pointer 'aPtr'
	printf( "%p", *&aPtr );
	
	//prints the address to 'a'
	printf( "%p", &*aPtr );
	
	//prints the value of 'a'
	printf( "%d", *&a );
	
	//produces an error since 'a' is not a pointer
	//printf( "%d", &*a );
	return 0;
}
*/


//B

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20   

//function prototypes
void FillArray ( int *array, int size );
void PrintArray ( int *array, int size );
void BubbleSort ( int *array, int size );
void Swap ( int *x, int *y );


int main(void){
	int NumList[SIZE] = {0};
	srand(time(NULL));
	
	//calling all functions
	FillArray(NumList, SIZE);
	printf("Unsorted Array:\n");
	PrintArray(NumList, SIZE);
	BubbleSort(NumList, SIZE);
	printf("\nSorted Array:\n");
	PrintArray(NumList, SIZE);
	return 0;
}

/*
Objective: Print each element of the array to the user
Input: 'NumList' and 'SIZE' as input parameters
Output: Prints to the user
*/
void PrintArray(int *array, int size){
	for (int i=0; i<size; i++){
		printf("%d ", *(array+i));
	}
}

/*
Objective: Fill the array with random numbers between 0-100
Input: 'NumList' and 'SIZE' as input parameters
Output: Randomly filled array
*/
void FillArray(int *array, int size){
	for (int i=0; i<size; i++){
		*(array+i) = rand() % 101;
	}
}

/*
Objective: Sort the array in decreasing order using a bubble sort algorithm
Input: 'NumList' and 'SIZE' as input parameters
Output: Sorted array through pointers
*/
void BubbleSort(int *array, int size){
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			//if current j element is larger than i element they are swapped
			if (*(array+i) > *(array+j)){
				Swap((array+i), (array+j));
			}
		}
	}
}

/*
Objective: To swap to numbers
Input: Two integer values to be swapped
Output: Two swapped variables
*/ 
void Swap(int*x, int*y){
	int temp = *x;
	*x = *y;
	*y = temp;
}



