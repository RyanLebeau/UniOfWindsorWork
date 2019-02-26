/*
Edited by: Ryan Lebeau
06/12/2016
globalStack.c
*/

#include <stdio.h>
#define STACK_Size 6      

          

int isEmpty(int top);
int isFull(int top);
int pop(int contents[], int*);
int push(int data, int*, int*);

int main() {
	int contents[STACK_Size];
	int *contptr;
	contptr = contents;
	int top = 0;  
	
   // push items on to the contents 
   push(3, contptr, &top);
   push(5, contptr, &top);
   push(9, contptr, &top);
   push(1, contptr, &top);
   push(12, contptr, &top);
   push(15, contptr, &top);
   
   printf("contents full: %s\n" , isFull(top)?"true":"false");
   printf("contents empty: %s\n" , isEmpty(top)?"true":"false");
   
   printf("Elements: \n");

   // print contents data 
   while(!isEmpty(top)) {
      int data = pop(contents, &top);
      printf("%d\n",data);
   }

   printf("contents full: %s\n" , isFull(top)?"true":"false");
   printf("contents empty: %s\n" , isEmpty(top)?"true":"false");
   
   return 0;
}

int isEmpty(int top) {

   if(top == 0)
      return 1;
   else
      return 0;
}
   
int isFull(int top) {

   if(top == STACK_Size)
      return 1;
   else
      return 0;
}

int pop(int contents[], int *top) {
   int data;
	
   if(!isEmpty(*top)) {
      *top -= 1; 
	  data = contents[*top];
      return data;
   } else {
      printf("Could not retrieve data, contents is empty.\n");
   }
}

int push(int data, int *contptr, int *top) {

   if(!isFull(*top)) {
      *(contptr + *top) = data;
	  *top += 1; 
   } else {
      printf("Could not insert data, contents is full.\n");
   }
}
