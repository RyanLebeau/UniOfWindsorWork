/*
Ryan Lebeau
25/03/2017
assign4.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//creating the structure
struct CourseInfo{
	int courseID;
	char courseName[50];
	char courseCode[12];
	char Term [6];
};
typedef struct CourseInfo CInfo;

//function declarations
void loadCourseInfo(CInfo *cinfo, FILE *inputCourse);
void displayCourseInfo(CInfo *cinfo, int*);
void addCourseInfo(CInfo *cinfo, int*);
int searchCourseInfo(CInfo *cinfo, char *, int*);

int main (void){
	//openeing input.csv and storing it in inputCourse
	FILE *inputCourse;
	inputCourse = fopen("input.csv", "r");
	int numOfCourse=4, done=0, choice;
	char search[50];
	//creating a dunamic array of structures with type CourseInfo
	CInfo *cinfo = (CInfo*)malloc(numOfCourse*sizeof(CInfo));
	
	loadCourseInfo(cinfo, inputCourse);
	displayCourseInfo(cinfo, &numOfCourse);
	//menu loop that runs until user exits
	while(!done){
		printf("Enter 1 to add information, 2 to search courseID/Name, 3 to exit: ");
		scanf("%d", &choice);
		//if user enters 1 add a course 
		if (choice==1){
			addCourseInfo(cinfo, &numOfCourse);
			displayCourseInfo(cinfo, &numOfCourse);
			printf("\n");
		}
		//if user enters 2 search a course
		else if (choice==2){
			printf("Enter a course id or name to search: ");
			scanf("%s", search);
			searchCourseInfo(cinfo, search, &numOfCourse);
			printf("\n");
		}
		else
			done=1;
	}
}

/*
Objective: Gather all courses from the input file and load into cinfo structures
Input: Dynamic array of structers and input file as parameters
Output: Array of structures populated with all inputs
*/
void loadCourseInfo(CInfo *cinfo, FILE *inputCourse){
	int j=0;
	char input[256],subject[10],level[10],section[10],semester[10],year[10];
	//loop that runs for number of initial inputs
	for (int i=0;i<4;i++){
		fscanf(inputCourse, "%s", input);
		//splits the input line into words with "," as a delimiter
		char *token = strtok(input, ",");
		while(token!=NULL){	
		//storing each input word into appropriate variables
			switch(j){
				//handling the course info input
				case 0: 
					strcpy(cinfo[i].courseName, token); 
					for (int k=0; k<strlen(cinfo[i].courseName); k++){
						cinfo[i].courseName[k] = toupper(cinfo[i].courseName[k]);
					}
					break;
				//handling the course code input, code is split among multiple inputs
				case 1: strcpy(cinfo[i].courseCode, token); break;
				case 2: strcat(cinfo[i].courseCode, token); break;
				case 3: 
					strcat(cinfo[i].courseCode, "-");
					strcat(cinfo[i].courseCode, token);
					break;
				case 4: 
					strcat(cinfo[i].courseCode, "-");
					strcat(cinfo[i].courseCode, token);
					break;
				//handling the term input
				case 5: strcpy(cinfo[i].Term, token); break;
				case 6: strcat(cinfo[i].Term, token); break;
				default: break;
			}
			//moving to the next word
			token = strtok(NULL, ",");
			j += 1;
		}
		j=0;
		cinfo[i].courseID = i+1;
	}
}

/*
Objective: Displays course information to the user
Input: Dynamic array of structures and number of inputs as parameters
Output: Prints all inputs to the user
*/
void displayCourseInfo(CInfo *cinfo, int *numCoursePtr){
	char id[]="ID", name[]="Name", code[]="Code", term[]="Term";
	//from 0 to the number of inputs
	for (int i=0;i<*numCoursePtr;i++){
		if (i==0)
			printf("%-5s%-15s%-15s%-5s\n", id, name, code, term);
		printf("%-5d%-15s%-15s%-5s\n", cinfo[i].courseID, cinfo[i].courseName, cinfo[i].courseCode, cinfo[i].Term);
	}
}

/*
Objective: Allow the user to add more course information
Input: Dynamic array of structures and number of inputs as parameters
Output: Updated course structures
*/
void addCourseInfo(CInfo *cinfo, int *numCoursePtr){
	int flag=0;
	*numCoursePtr += 1;
	//new id as number of inputs
	cinfo[*numCoursePtr-1].courseID = *numCoursePtr;
	//loop that runs until user enters a unique course code
	while (!flag){
		//ask for and save user inputs
		printf("Enter new course information seperated by a space (Name Code Term): ");
		scanf("%s %s %s", cinfo[*numCoursePtr-1].courseName, cinfo[*numCoursePtr-1].courseCode, cinfo[*numCoursePtr-1].Term);
		//searches for similar course codes and informs user if it is repeated
		for (int i=0;i<*numCoursePtr-1;i++){
			if (!strcmp(cinfo[*numCoursePtr-1].courseCode, cinfo[i].courseCode)){
				printf("The course code must be unique.\n");
				break;
			}
			else if (i==*numCoursePtr-2)
				flag=1;
		}
	}
	//capitalizes the inputted course name
	for (int j=0; j<strlen(cinfo[*numCoursePtr-1].courseName); j++){
		cinfo[*numCoursePtr-1].courseName[j] = toupper(cinfo[*numCoursePtr-1].courseName[j]);
	}
}

/*
Objective: Search the course info by id or course name
Input: Dynamic array of structres, user inuputed id/name, and number of total inputs as parameters
Output: Prints the corresponding course info to searched id/name
*/
int searchCourseInfo(CInfo *cinfo, char *word, int *numCoursePtr){
	int value;
	//capitalizes the inputted name
	for (int k=0; k<strlen(word); k++){
			word[k] = toupper(word[k]);
		}
	//loop that runs for number of inputs
	for (int i=0;i<*numCoursePtr;i++){
		//converts the input id into a str value
		value = atoi(word);
		//if course name is found the print to user and exit function
		if(!strcmp(cinfo[i].courseName, word)){
			printf("%-5d%-15s%-15s%-5s\n", cinfo[i].courseID, cinfo[i].courseName, cinfo[i].courseCode, cinfo[i].Term);
			return 0;
		}
		//if course id is found print to user and exit function
		else if(value==cinfo[i].courseID){
			printf("%-5d%-15s%-15s%-5s\n", cinfo[i].courseID, cinfo[i].courseName, cinfo[i].courseCode, cinfo[i].Term);
			return 0;
		}
	}
	//if there is no course to the entered id/name
	printf("There is no course linked to that name or ID.\n");
}






