/*
Ryan Lebeau
29/03/2017
assign5.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//courseInfo structure definition
struct CourseInfo{
	int courseID;
	char courseName[30];
};
typedef struct CourseInfo CInfo;

//studentInfo structure definition
struct studentInfo{
	char StudentID[10];
	char FirstName[20];
	char LastName[25];
	int numCourses;
	CInfo cinfo[10];
	struct studentInfo *link;
};
typedef struct studentInfo SInfo;
//creating the pointer node
SInfo *head = NULL;

//function declerations
int loadStudentInfo(FILE *input, int, int*);
void displayStudentInfo();
int searchStudentID(char[]);
void searchStudentName(char[]);
int addStudent();
int deleteStudent(char[]);
void saveStudentInfo(FILE *input2);

int main(void){
	int done=0, choice, i=0, stop=0;
	int*stopPtr;
	stopPtr=&stop;
	char name[256], enterID[256];
	//openeing the file with inputs to read
	FILE *input;
	input = fopen("studentList.txt", "r");
	//loop loadStudentIfno until all inputs read
	while (!stop){
		i = loadStudentInfo(input, i, &stop);
	}
	//loop that runs until user exits
	while(!done){
		printf("\n1.Add new student\n2.Delete a student\n3.Search for a student\n4.Display current students\n5.Save student information to file\n6.Exit\n");
		printf("Please enter a selection: ");
		scanf("%d", &choice);
		//switch based on user inputted choice
		switch(choice){
			//adding a new student
			case 1: 
				printf("--Adding new student--\n");
				addStudent();
				break;
			//deleting a student
			case 2:
				printf("Enter a student ID to remove: ");
				scanf("%s", enterID);
				deleteStudent(enterID);
				break;
			//searching for a student by last name
			case 3: 
				printf("Enter a student last name: ");
				scanf("%s", name);
				searchStudentName(name); 
				break;
			//printing students to the user
			case 4: displayStudentInfo(); break;
			//saving students
			case 5:
				//close current input 
				fclose(input);
				//open again with "w" to wipe and rewrite
				FILE *input2;
				input2 = fopen("studentList.txt", "wb");
				saveStudentInfo(input2);
				//close and open again to read
				fclose(input2);
				FILE *input = fopen("studentList.txt", "r");
				break;
			//exiting the program
			case 6: 
				//reopen with "w" to save 
				fclose(input);
				input2 = fopen("studentList.txt", "wb");
				saveStudentInfo(input2);
				fclose(input2);
				//exiting the while loop
				done=1;
				break;
			default: printf("That is not a valid option");
		}
		
	}
}

/*
Objective: Load student info from 'studentList.txt' and store into sorted link list
Input: File, number of inputs ('i'), and pointer to 'stop' as parameters
Output: Sorted link list and returns value of 'i'
*/
int loadStudentInfo(FILE* input, int i, int*stopPtr){
	int repeat=1, numCourse, num, j, numInputID, numID, k, check;
	char inputLine[256];
	//creating temp nodes
	SInfo* temp = (SInfo*)malloc(sizeof(SInfo));
	//loop that runs until inputs are done
	for(;repeat;i++){
		//student id
		fscanf(input, "%s", inputLine);
		//end of inputs
		if (!strcmp(inputLine, "***")){
			repeat=0;
			*stopPtr = 1;
			break;
		}
		strcpy(temp->StudentID, inputLine);
		strcpy(inputLine, "");
		//students first name
		fscanf(input, "%s", inputLine);
		strcpy(temp->FirstName, inputLine);
		strcpy(inputLine, "");
		//students last name
		fscanf(input, "%s", inputLine);
		strcpy(temp->LastName, inputLine);
		strcpy(inputLine, "");
		//number of student courses
		fscanf(input, "%s", inputLine);
		numCourse = atoi(inputLine);
		temp->numCourses = numCourse;
		strcpy(inputLine, "");
		
		for(j=0;j < (temp->numCourses);j++){
			//course name
			fscanf(input, "%s", inputLine);
			strcpy(temp->cinfo[j].courseName, inputLine);
			strcpy(inputLine, "");
			//course id
			fscanf(input, "%s", inputLine);
			num = atoi(inputLine);
			temp->cinfo[j].courseID = num;
			strcpy(inputLine, "");
		}
		temp->link = NULL;
		int k=0;
		//if first input
		if(i==0){
			head=temp;
			temp = (SInfo*)malloc(sizeof(SInfo));
		}
		//if second input
		else if(i==1){
			SInfo *next;
			next = head;
			numInputID = atoi(temp->StudentID);
			numID = atoi(next->StudentID);
			//check if the current node id is less than next node id
			if (numID>numInputID){
				temp->link = head;
				head = temp;
			}
			//if not set last element to current node
			else{
				next->link = temp;
			}
			temp = (SInfo*)malloc(sizeof(SInfo));
		}
		//sorting for inputs after the second
		else{
			//creating nodes reference to the linked list
			temp->link = NULL;
			SInfo *next,*prev,*first;
			next = head;
			prev = NULL;
			//counter variables
			k=0, check=0;
			numInputID = atoi(temp->StudentID);
			//loop until on the last element
			while (next->link != NULL){
				numID = atoi(next->StudentID);
				if (numID>numInputID){
					if (k==0){
						temp->link = head;
						head = temp;
					}
					else{
						prev->link = temp;
						temp->link = next;
					}
					return i;
				}
				//continue to the next element and advance 'prev'
				else{
					prev=next;
					next=next->link;
					k++;
				}
			}
			//if on the last element run code to sort
			numID = atoi(next->StudentID);
			if (numID>numInputID){
				prev->link = temp;
				temp->link = next;
			}
			else{
				next->link = temp;
				temp->link = NULL;
			}
			
			temp = (SInfo*)malloc(sizeof(SInfo));
		}
	}
}

/*
Objective: Print linked list to the user
Input: No input
Output: Prints linked list and all elements inside
*/
void displayStudentInfo(){
	int i=0;
	//set onde pointing to first element
	SInfo*temp1 = head;
	//loops until on last element
	while(temp1->link != NULL){
		//printing to user
		printf("%s\n%s\n%s\n%d\n", temp1->StudentID,temp1->FirstName,temp1->LastName,temp1->numCourses);
		for (i=0;i< temp1->numCourses;i++)
			printf("%s %d\n", temp1->cinfo[i].courseName, temp1->cinfo[i].courseID);
		temp1 = temp1->link;
	}
	//printing last element to user
	printf("%s\n%s\n%s\n%d\n", temp1->StudentID,temp1->FirstName,temp1->LastName,temp1->numCourses);
	for (i=0;i< temp1->numCourses;i++)
		printf("%s %d\n", temp1->cinfo[i].courseName, temp1->cinfo[i].courseID);
	
}

/*
Objective: Search for student by ID
Input: ID to be searched as a parameter
Output: Returns 1 if ID was found returns 0 if not
*/
int searchStudentID(char searchID[256]){
	int intSearchID = atoi(searchID);
	int intStudentID;
	SInfo*temp1 = head;
	//loop that runs until last element
	while(temp1->link != NULL){
		//converting current node ID to int
		intStudentID = atoi(temp1->StudentID);
		if (intStudentID==intSearchID)
			return 1;
		//moving to next element
		temp1 = temp1->link;
	}
	//for last element
	if (intStudentID==intSearchID)
			return 1;
	return 0;
}

/*
Objective: Search linked list for a student's last name
Input: Name to be searched for as a parameter
Output: Prints corresponding student info with last name
*/
void searchStudentName(char name[256]){
	SInfo*temp1 = head;
	//changes first character to capital for comparing
	if (name[0]!=toupper(name[0]))
		name[0] = toupper(name[0]);
	//loop that runs until last element
	while(temp1->link != NULL){
		//if last name is in current element
		if(!strcmp(name, temp1->LastName)){
			printf("%s\n%s\n%s\n%d\n", temp1->StudentID,temp1->FirstName,temp1->LastName,temp1->numCourses);
			for (int i=0;i< temp1->numCourses;i++)
				printf("%s %d\n", temp1->cinfo[i].courseName, temp1->cinfo[i].courseID);
		}
		//continue to next element
		temp1 = temp1->link;
	}
	//for last element
	if(!strcmp(name, temp1->LastName)){
		printf("%s\n%s\n%s\n%d\n", temp1->StudentID,temp1->FirstName,temp1->LastName,temp1->numCourses);
		for (int i=0;i< temp1->numCourses;i++)
			printf("%s %d\n", temp1->cinfo[i].courseName, temp1->cinfo[i].courseID);
	}
}

/*
Objective: Add student to sorted linked list
Input: No input
Output: Updated linked list wiht new student sorted
*/
int addStudent(){
	int intID, intStructID;
	char name[256], id[10];
	//creating node at beginnning of linked list
	SInfo* temp = (SInfo*)malloc(sizeof(SInfo));
	printf("Student ID: ");
	scanf("%s", id);
	//if student id is repeated
	if(searchStudentID(id)){
		printf("Student ID must be unique.");
		return 0;
	}
	strcpy(temp->StudentID, id);
	//storing First Name
	printf("First Name: ");
	scanf("%s", name);
	name[0] = toupper(name[0]);
	strcpy(temp->FirstName, name);
	strcpy(name, "");
	//storing Last Name
	printf("Last Name: ");
	scanf("%s", name);
	name[0] = toupper(name[0]);
	strcpy(temp->LastName, name);
	strcpy(name, "");
	//Storing number of courses
	printf("Number of courses: ");
	scanf("%d", &temp->numCourses);
	//for loop to store course info runs number of courses
	for(int i=0;i< temp->numCourses; i++){
		printf("Course ID: ");
		scanf("%d", &temp->cinfo[i].courseID);
		printf("Course Name: ");
		scanf("%s", temp->cinfo[i].courseName);
	}
	//creating nodes to sort new student into linked list
	temp->link = NULL;
	intID = atoi(temp->StudentID);
	SInfo *next, *prev;
	next = head;
	prev = NULL;
	int i=0;
	//loop that runs until last element
	while(next->link != NULL){
		intStructID = atoi(next->StudentID);
		if (intStructID>intID){
			//if first element
			if(i==0){
				temp->link = head;
				head = temp;
				return 0;
			}
			else{
				prev->link = temp;
				temp->link = next;
				return 0;
			}
		}
		//continue to next elment
		else{
			prev = next;
			next = next->link;
		}
		i++;
	}
	//for last element in linke dlist
	intStructID = atoi(next->StudentID);
	if (intStructID>intID){
		prev->link = temp;
		temp->link = next;
		return 0;
	}
	else if (intStructID<intID){
		next->link = temp;
		return 0;
	}
	
	return 0;
}

/*
Objective: Remove student from linked list
Input: ID of student to remove as a parameter
Output: Return 0 when student removed
*/
int deleteStudent(char enterID[256]){
	int intEnterID = atoi(enterID), i=0, intStudentID;
	//creating nodes to linked list to find ID
	SInfo*next, *prev;
	next = head;
	prev = NULL;
	//loop that runs until last element
	while(next->link != NULL){
		intStudentID = atoi(next->StudentID);
		if (intStudentID==intEnterID){
			//if first element
			if(i==0){
				head = next->link;
				return 0;
			}
			else{
				prev->link = next->link;
				free(next);
				return 0;
			}
		}
		//continue to next element
		prev = next;
		next = next->link;
		i++;
	}
	//for last element
	intStudentID = atoi(next->StudentID);
	if (intStudentID==intEnterID){
		prev->link = NULL;
		free(next);
	}
	
}

/*
Objective: Save student info to text file
Input: Text file as a parameter
Output: Updated text file
*/
void saveStudentInfo(FILE *input2){
	SInfo *temp=head;
	//loop that runs until last element
	while(temp->link!=NULL){
		//printing current element into the text file
		fprintf(input2, "%s\n%s\n%s\n%d\n", temp->StudentID,temp->FirstName,temp->LastName,temp->numCourses);
		for (int i=0;i< temp->numCourses;i++)
			fprintf(input2, "%s %d\n", temp->cinfo[i].courseName, temp->cinfo[i].courseID);
		//continue to next element
		temp = temp->link;
	}
	//for last element
	fprintf(input2, "%s\n%s\n%s\n%d\n", temp->StudentID,temp->FirstName,temp->LastName,temp->numCourses);
	for (int i=0;i< temp->numCourses;i++)
		fprintf(input2, "%s %d\n", temp->cinfo[i].courseName, temp->cinfo[i].courseID);
	fprintf(input2, "***");
}

