/*
Ryan Lebeau
27/09/2017
Data Structures & Algorithms
Assign1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//postInfo structure definition
struct postInfo{
	char accountName[256];
	char strDate[20];
	int numLikes,numComments,numCharacters, numDate;
	struct postInfo *link;
};
typedef struct postInfo PInfo;
//creating the pointer node
PInfo *head = NULL;

//function declerations
int menu(void);
void displayStoredPosts(void);
void displayFirstPost(void);
int numberOfPosts(void);
void enterNewPost(void);
int deletePost(void);
void deleteAllPosts(void);
int sortPosts(PInfo **);
void insertSort(PInfo **, PInfo *, int);
int dateToInt(char *);

int main(void){
	int finishFlag = 0, userChoice, deletion=0, tempi=0;
	
	//Populating with posts
	char nam[]="Ryan";
	char dat[20]="2012/04/20";
	int numLike=5,numComment=4,numCharacter=144, numDat=20170925;
	PInfo *temp = (PInfo*)malloc(sizeof(PInfo));
	strcpy(temp->accountName, nam);
	strcpy(temp->strDate, dat);
	temp->numLikes = numLike;
	temp->numComments = numComment;
	temp->numCharacters = numCharacter;
	temp->link = NULL;
	int i=0;
	//if first input
	if(i==0){
		head=temp;
		temp = (PInfo*)malloc(sizeof(PInfo));
	}
	char name1[]="Lebeau";
	char date[20]="2006/09/25";
	numLike=10,numComment=8,numCharacter=6, numDat=20170952;
	strcpy(temp->accountName, name1);
	strcpy(temp->strDate, date);
	temp->numLikes = numLike;
	temp->numComments = numComment;
	temp->numCharacters = numCharacter;
	temp->link = NULL;
	PInfo *next;
	next = head;
	//while the next element is not null
	while(next->link!=NULL){
		//continue to the next element
		next=next->link;
	}
	next->link = temp;
	
	//loop that repeates until user exits
	while(!finishFlag){
		userChoice = menu();
		//switch that handles users input choice
		switch(userChoice){
			//display all posts
			case 1:
				//if all posts have been deleted
				if(!deletion)
					displayStoredPosts();
				else
					printf("There are no posts.\n\n");
				break;
			//display first post
			case 2:
				//if all posts havebeen deleted
				if(!deletion)
					displayFirstPost();
				else
					printf("There are no posts.\n\n");

				break;
			//number of posts
			case 3:
				printf("Number of posts: %d\n\n", numberOfPosts());
				break;
			//entering a new post
			case 4:
				if (deletion)
					deletion=0;
				enterNewPost();
				break;
			//deleting a post
			case 5:
				tempi = deletePost();
				break;
			//deleting all posts
			case 6:
				deletion=1;
				deleteAllPosts();
				break;
			//sort
			case 7:
				sortPosts(&head);
				printf("\n");
				break;
			//exit
			case 8:
				printf("Exiting...");
				finishFlag = 1; 
				break;
			
		}
	};
	deleteAllPosts();	
}

/*
Objective: Prompt user with menu 
Input: User enters choice
Output: Return user choice
*/
int menu(void){
	int choice=0, flag=0;
	//repeatedly ask for user input if not a possible choice
	while(!flag){
		printf("1.Display Stored Posts\n2.Search First Post\n3.Display Current Number of Posts\n4.Enter a New Post\n5.Delete a Post\n6.Delete all Posts\n7.Sort the Posts\n8.Exit\n");
		printf("Please enter desired choice by number: ");
		scanf("%d", &choice);
		if(choice<1 || choice>8){
			printf("That is not an option.\n\n");
		}
		else
			flag=1;
	}
	return choice;
}

/*
Objective: Display all stored posts
Input: No input
Output: Displays every post to user 
*/
void displayStoredPosts(void){
	//formatting
	printf("\n");
	//set node pointing to first element
	PInfo*temp1 = head;
	//loops until on last element
	while(temp1->link != NULL){
		//printing to user
		printf("Likes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n", temp1->numLikes,temp1->numComments,temp1->numCharacters,temp1->strDate,temp1->accountName);
		temp1 = temp1->link;
	}
	//printing last element to user
	printf("Likes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp1->numLikes,temp1->numComments,temp1->numCharacters,temp1->strDate,temp1->accountName);
	
}

/*
Objective: Display post chosen by user
Input: User enters search fields
Output: Post matching eneterd search or no port found
*/
void displayFirstPost(void){
	int userChoice=0, userNum;
	char userStr[256];
	//menu
	printf("\n1.Search by Likes\n2.Search by Comments\n3.Search by Characters\n4.Search by Author\n5.Search by Date");
	printf("\nEnter a search method(by number): ");
	scanf("%d", &userChoice);
	printf("Search: ");
	scanf("%s", userStr);
	
	PInfo *temp;
	temp = head;
	//switch to handle different searches for each choice
	switch(userChoice){
		//searching by likes
		case 1:
			userNum = atoi(userStr);
			while(temp->link !=NULL){
				//if the current node numbervof likes is the same as user entered
				if(temp->numLikes == userNum){
					printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
					break;
				}
				else{
					temp=temp->link;
				}
			}
			//last node
			if(temp->link == NULL && temp->numLikes == userNum){
				printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
			}
			else if(temp->link == NULL){
				printf("There is no post that with that amount of likes.\n");
			}
			break;
		//searching by comments
		case 2:
			userNum = atoi(userStr);
			while(temp->link !=NULL){
				//current node number of comments is user entered number
				if(temp->numComments == userNum){
					printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
					break;
				}
				else{
					temp=temp->link;
				}
			}
			//last node
			if(temp->link == NULL && temp->numComments == userNum){
				printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
			}
			else if(temp->link == NULL){
				printf("There is no post that with that amount of comments.\n");
			}
			break;
		//search by characters
		case 3:
			userNum = atoi(userStr);
			while(temp->link !=NULL){
				//if the numbe rof characters in node match entered number
				if(temp->numCharacters == userNum){
					printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
					break;
				}
				else{
					temp=temp->link;
				}
			}
			//last node
			if(temp->link == NULL && temp->numCharacters == userNum){
				printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
			}
			else if(temp->link == NULL){
				printf("There is no post that with that amount of characters.\n");
			}
			break;
		//search by author
		case 4:
			//lower case user input
			for(int k=2;k < strlen(userStr);k++){
				userStr[k] = tolower(userStr[k]);
			}
			while(temp->link!=NULL){
				//lower case entered post
				for(int k=0;k < strlen(temp->accountName);k++){
					temp->accountName[k] = tolower(temp->accountName[k]);
				}
				//found match at node
				if (strcmp(userStr, temp->accountName) == 0){
					printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
					break;
				}
				else{
					temp=temp->link;
				}
			}
			//last node
			if(temp->link == NULL && strcmp(userStr, temp->accountName) == 0){
				printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
			}
			else if(temp->link == NULL){
				printf("There is no post that with that author.\n");
			}
			break;
		//search by date
		case 5:
			while(temp->link!=NULL){
				//found match at node
				if (strcmp(userStr, temp->strDate) == 0){
					printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
					break;
				}
				else{
					temp=temp->link;
				}
			}
			//last node
			if(temp->link == NULL && strcmp(userStr, temp->strDate) == 0){
				printf("\nLikes: %d\nComments: %d\nCharacters: %d\nDate: %s\nAccount: %s\n\n", temp->numLikes,temp->numComments,temp->numCharacters,temp->strDate,temp->accountName);
			}
			else if(temp->link == NULL){
				printf("There is no post made on that date.\n\n");
			}
			break;	
	}
	deleteAll
}

/*
Objective: Count the number of posts
Input: No inputs
Output: Returns the number of posts
*/
int numberOfPosts(void){
	int j=0;
	//set node pointing to first element
	PInfo*temp1 = head;
	//loops until the last element
	while(temp1->link != NULL){
		temp1 = temp1->link;
		j++;
	}
	return ++j;
}

/*
Objective: User enters a new post
Input: User enters post data
Output: Saves node in linked list
*/
void enterNewPost(void){
	char author[256];
	char date[20];
	int numLike,numComment,numCharacter;
	PInfo *temp = (PInfo*)malloc(sizeof(PInfo));
	//user enters
	printf("Enter author: "); scanf("%s", author);
	printf("Enter date(yyyy/mm/dd): "); scanf("%s", date);
	printf("Enter number of likes(integer): "); scanf("%d", &numLike);
	printf("Enter number of comments(integer): "); scanf("%d", &numComment);
	printf("Enter number of characters(integer): "); scanf("%d", &numCharacter);
	//assigning values to post node
	strcpy(temp->accountName, author);
	strcpy(temp->strDate, date);
	temp->numLikes = numLike;
	temp->numComments = numComment;
	temp->numCharacters = numCharacter;
	temp->link = NULL;
	PInfo *next;
	next = head;
	//while the next element is not null
	while(next->link!=NULL){
		//continue to the next element
		next=next->link;
	}
	next->link = temp;
	//formatting
	printf("\n");
}

/*
Objective: Delete a post by author or date
Input: Search field for delete entered by user
Output: Returns 0 when deletion is complete
*/
int deletePost(void){
	//asking user which post to be deleted
	int userChoiceInt;
	char userSearch[256];
	printf("Enter either post author or date(1_author, 2_yyyy/mm/dd): ");
	scanf("%d_%s", &userChoiceInt, userSearch);
	
	PInfo *next, *prev;
	next=head;
	prev=NULL;
	//if user chose author
	if(userChoiceInt == 1){
		//lower case user input
		for(int k=2;k < strlen(userSearch);k++){
			userSearch[k] = tolower(userSearch[k]);
		}
		while(next->link!=NULL){
			//lower case entered post
			for(int k=0;k < strlen(next->accountName);k++){
				next->accountName[k] = tolower(next->accountName[k]);
			}
			//found match at node
			if (strcmp(userSearch, next->accountName) == 0){
				//if head node being removed
				if (prev==NULL){
					head=next->link;
					return 0;
				}
				//any other node
				else{
					prev->link=next->link;
					return 0;
				}
			}
			//not a match continue to next node
			else{
				prev = next;
				next = next->link;
			}	
		}
		//last node
		//lower case entered post
		for(int k=0;k < strlen(next->accountName);k++){
			next->accountName[k] = tolower(next->accountName[k]);
		}
		if (strcmp(userSearch, next->accountName) == 0){
			prev->link = NULL;
			return 0;
		}
		else{
			printf("That author does not exist.\n");
			return 0;
		}
	}
	
	//date
	else if (userChoiceInt == 2){
		while(next->link!=NULL){
			//found match at node
			if (strcmp(userSearch, next->strDate) == 0){
				//if head node being removed
				if (prev==NULL){
					head=next->link;
					return 0;
				}
				//any other node
				else{
					prev->link=next->link;
					free(next);
					return 0;
				}
			}
			//not a match continue to next node
			else{
				prev = next;
				next = next->link;
			}	
		}
		//last node
		if (strcmp(userSearch, next->strDate) == 0){
			prev->link = NULL;
			return 0;
		}
		else{
			printf("That date does not exist on an entered post.\n");
			return 0;
		}
	}
	//if entered number is not valid
	else{
		printf("That numerical option is incorrect.\n");
	}
}

/*
Objective: Delete every post
Input: No input
Output: Displays to user that posts were deleted
*/
void deleteAllPosts(void){
	PInfo *temp;
	while(head!=NULL){
		//skip current node
		temp=head;
		head=head->link;
		//free node
		free(temp);
	}
	printf("All posts deleted.\n\n");
}

/*
Objective: Sort posts by a user desired field
Input: Head node as a reference
Output: Returns 0 when complete, sorted linked list
*/
int sortPosts(PInfo **reference){
	int choice;
	printf("How would you like to sort?(1.Likes 2.Comments 3.Characters 4.Date): ");
	scanf("%d", &choice);
	if(choice<1 || choice>4){
		printf("That is not a valid choice.");
		return 0;
	}
	//final sort controls sorted linked list
	PInfo *finalSort = NULL;
	//temp node starting at head
	PInfo *temp = *reference;

	while(temp!=NULL){
		//create node at next position
		PInfo *next = temp->link;
		//call sorting function
		insertSort(&finalSort, temp, choice);
		//updating the temp node
		temp = next;
	}
	//changes reference to the sorted linked list
	*reference = finalSort;
	return 0;
}

/*
Objective: Inserts node in correct sorted position
Input: Reference to head node, the tmep node to be inserted, user choice for sorting
Output: Returns 1 if ID was found returns 0 if not
*/
void insertSort(PInfo **reference, PInfo *insert, int choice){
	//switch case handles which way to sort
	switch(choice){
		//sort by likes
		case 1:
			//if head node
			if(*reference == NULL || (*reference)->numLikes >= insert->numLikes){
				//sets insert to head node reference
				insert->link = *reference;
				*reference = insert;
			}
			//if not head node
			else{
				PInfo *temp;
				temp = *reference;
				//finding position for insert
				while(temp->link!=NULL && temp->link->numLikes < insert->numLikes){
					temp = temp->link;
				}
				//setting insert in the linke dlist at current position
				insert->link = temp->link;
				temp->link = insert;
			}
			break;
		//sort by comments
		case 2:
			if(*reference == NULL || (*reference)->numComments >= insert->numComments){
				insert->link = *reference;
				*reference = insert;
			}
			else{
				PInfo *temp;
				temp = *reference;
				while(temp->link!=NULL && temp->link->numComments < insert->numComments){
					temp = temp->link;
				}
				insert->link = temp->link;
				temp->link = insert;
			}
			break;
		//sort by characters
		case 3:
			if(*reference == NULL || (*reference)->numCharacters >= insert->numCharacters){
				insert->link = *reference;
				*reference = insert;
			}
			else{
				PInfo *temp;
				temp = *reference;
				while(temp->link!=NULL && temp->link->numCharacters < insert->numCharacters){
					temp = temp->link;
				}
				insert->link = temp->link;
				temp->link = insert;
			}
			break;
		//sort by date
		case 4:
			if(*reference!=NULL){
				(*reference)->numDate = dateToInt((*reference)->strDate);
			}
			
			insert->numDate = dateToInt(insert->strDate);
			if(*reference == NULL || (*reference)->numDate >= insert->numDate){
				insert->link = *reference;
				*reference = insert;
			}
			else{
				PInfo *temp;
				temp = *reference;
				temp->numDate = dateToInt(temp->strDate);
				while(temp->link!=NULL && temp->link->numDate < insert->numDate){
					temp = temp->link;
					temp->numDate = dateToInt(temp->strDate);
				}
				insert->link = temp->link;
				temp->link = insert;
			}
			
			break;
		
	}
}

/*
Objective: Change node string date to integer
Input: String date from node
Output: Returns date in an int
*/
int dateToInt(char *strDate){
	char tempDate[10];
	int intDate;
	//transfers numbers from strDate to temp string, skipping '/'s
	for(int i=0; i<8; i++){
		if(i<4)
			tempDate[i] = strDate[i];
		else if (i>=4 && i<6)
			tempDate[i] = strDate[i+1];
		else
			tempDate[i] = strDate[i+2];
	}
	intDate= atoi(tempDate);
	return intDate;
}












