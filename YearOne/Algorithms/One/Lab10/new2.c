#include <stdio.h>
#define STACK_Size 6      

           

int isEmpty(int top);
int isFull(int top);
int pop(int contents[], int top);
int push(int data, int contents[], int top);

int main() {
	int contents[STACK_Size];     
	int top = 0; 
   // push items on to the contents 
   contents[top] = 3;
   top ++;
   push(3, contents, top);
   contents[top] = 5;
   top++;
   push(5, contents, top);
   contents[top] = 9;
   top++;
   push(9, contents, top);
   contents[top] = 1;
   top++;
   push(1, contents, top);
   contents[top] = 12;
   top++;
   push(12, contents, top);
   contents[top] = 15;
   top++;
   push(15, contents, top);
   
   printf("contents full: %s\n" , isFull(top)?"true":"false");
   printf("contents empty: %s\n" , isEmpty(top)?"true":"false");
   
   printf("Elements: \n");
   top--;
   // print contents data 
   while(!isEmpty(top)) {
	   //top = top -1;
      int data = pop(contents, top);
      printf("%d\n",data);
	  top = top -1;
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

int pop(int contents[], int top) {
   int data;
	
   if(!isEmpty(top)) {
      //top = top - 1; 
	  data = contents[top];
      return data;
   } else {
      //printf("Could not retrieve data, contents is empty.\n");
   }
}

int push(int data, int contents[], int top) {

   if(!isFull(top)) {
      contents[top] = data;
	  //top = top + 1; 
   } else {
      //printf("Could not insert data, contents is full.\n");
   }
}
