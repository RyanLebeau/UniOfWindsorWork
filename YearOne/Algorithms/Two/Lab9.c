/*
Ryan Lebeau
29/03/2017
Lab9.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//creating structure of student
struct student {
   int ID;
   char name[40];
   struct student *next;
};
typedef struct student Student;

//function declarations 
int getChoice();
Student *addToList(Student *List);
void printList(Student *List);
void printListRR(Student *List);
void searchList(Student *List);

int main() {
    int choice = 0;
	//creating pointer to first node
    Student *SLIST = NULL;
	//gets choice from user
    choice = getChoice();

    while(choice >= 0)  {
		//calls function linked to number in 'getChoice'
        switch(choice) {
            case 0 : printf("Bye...\n"); exit(0);
            case 1 : SLIST = addToList(SLIST); break;
            case 2 : printList(SLIST); break;
            case 3 : printListRR(SLIST); break;
            case 4 : searchList(SLIST); break;
            default: printf("That is not a valid choice\n");
        }
		//asks for next choice
        choice = getChoice();
    }
	//if SLIST is not empty free
    if(SLIST) 
		free(SLIST);
    return 0;
}

/*
Objective: Gather choice input from user
Input: No parameters in this function
Output: Returns the number that user picked
*/
int getChoice() {
    int choice = 0;
    printf("\n****** MENU ******\n");
    printf("1. Add new student to list.\n");
    printf("2. Print the student list, beginning to end.\n");
    printf("3. Recursively print the student list from the end.\n");
    printf("4. Search the list for a student.\n");
    printf("0. Quit.\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    return choice;
}

/*
Objective: Add students to List of students
Input: Pointer to the linked list initial node
Output: Returns the new linked list
*/
Student *addToList(Student *List){
	//create node to linked list called 'temp'
	Student *temp = (Student*)malloc(sizeof(Student));
	//user input 
	printf("Enter an ID: ");
	scanf("%d", &(temp->ID));
	printf("Enter a first name: ");
	scanf("%s", temp->name);
	temp->next = NULL;
	//if first element in the linked list
	if(List==NULL) 
		return temp;
	else{
		//if more than one element create node to first element
		Student *temp1=List;
		//while the next element is not null
		while(temp1->next!=NULL){
			//continue to the next element
			temp1=temp1->next;
		}
		temp1->next = temp;
		return List;
	}
	
}

/*
Objective: Print all elements in linked list
Input: Pointer to the linked list initial node
Output: Prints elements to the user
*/
void printList(Student *List){
	//while not the last element
	while(List!=NULL){
		printf("%d %s\n", List->ID, List->name);
		List=List->next;
	}
}

/*
Objective: Print all elements in linked list recursively
Input: Pointer to the linked list initial node
Output: Prints the elemets to the user
*/
void printListRR(Student *List){
	//if last element of linked list exit
	if(List==NULL)
		return;
	printListRR(List->next);
	printf("%d %s\n", List->ID, List->name);
}

/*
Objective: Search students by id and return id and name
Input: Pointer to the linked list initial node
Output: Prints the corresponding id and name
*/
void searchList(Student *List){
	int studentID;
	printf("Enter student ID: ");
	scanf("%d", &studentID);
	//while not last element of linked list
	while(List != NULL){
		if(studentID == List->ID){
			printf("%d %s\n", List->ID, List->name);
			return;
		}
		List = List->next;
	}
	printf("ID is not found");
}












