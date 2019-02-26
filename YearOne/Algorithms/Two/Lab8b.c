/*
Ryan Lebeau
22/03/2017
Lab8b.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//creating structure called employee
struct employee {
	char firstname[40];
	char lastname[40];
	int id;
	int GPA;
};
typedef struct employee Employee;

//function declarations
char WordCap(char *word);
void Save(const Employee *EmpList, FILE *EmpFile);

int main(void){
	//openening EmpFile to be read
	FILE *EmpFile;
	EmpFile = fopen("employee.dat", "rb+");
	Employee EmpList[3];
	//loop that runs for number of inputs
	for (int i=0; i<3; i++){
		//reading each input wihin employee.dat
		fscanf(EmpFile, "%d %s %s %d", &EmpList[i].id, EmpList[i].firstname, EmpList[i].lastname, &EmpList[i].GPA);
		//passing each capitalization through WordCap
		WordCap(EmpList[i].firstname);
		WordCap(EmpList[i].lastname);
	}
	//closing employee.dat
	fclose(EmpFile);
	//openening employee.dat to be rewrtten
	FILE *EmpFile2;
	EmpFile2 = fopen("employee.dat", "wb");
	Save(EmpList, EmpFile2);
	fclose(EmpFile2);
}

/*
Objective: Capitalize first letter of each word passed through
Input: Word to be capitalized passed as parameter
Output: Word is updated as pointer
*/
char WordCap(char *word){
	word[0] = toupper(word[0]);
}

/*
Objective: Update employee.dat with updated words
Input: Structure EmpList and employee.dat passed through as parameters
Output: employee.dat is updated
*/
void Save(const Employee *EmpList, FILE *EmpFile2){
	for (int i=0;i<3;i++){
		fprintf(EmpFile2, "%d %s %s %d\n", EmpList[i].id, EmpList[i].firstname, EmpList[i].lastname, EmpList[i].GPA);
	}
}

