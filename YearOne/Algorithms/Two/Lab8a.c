/*
Ryan Lebeau
22/03/2017
Lab8a.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A
//creating the first structure 'employee'
struct employee {
	char firstname[40];
	char lastname[40];
	int id;
	int GPA;
};
typedef struct employee Employee;

//function declarations
void InputEmpRecord(Employee *EmpList);
void PrintEmpList(const Employee *EmpList);
void SaveEmpList(const Employee *EmpList, FILE *FileName);

int main(void) {
	//openeing employee.dat to wrtie 
	FILE *EmpFile;
	EmpFile = fopen("employee.dat", "wb");
	Employee EmpList[3];
	//calling all functions
	InputEmpRecord(EmpList);
	printf("\n");
	PrintEmpList(EmpList);
	SaveEmpList(EmpList, EmpFile);
	//closing emplyoee.dat
	fclose(EmpFile);
}

/*
Objective: Take input from the user and store each input in EmpList structure
Input: Structure EmpList passed as a aparameter and three inputs from user
Output: EmpList values are changed within the scanf
*/
void InputEmpRecord(Employee *EmpList){
	for (int i=0;i<3;i++){
		printf("Enter a student(in form ID FIRST LAST GPA seperated by spaces): ");
		scanf("%d %s %s %d", &EmpList[i].id, EmpList[i].firstname, EmpList[i].lastname, &EmpList[i].GPA);
	}
}

/*
Objective: Print ID FIRSTNAME LASTNAME GPA to the user
Input: Structure EmpList passed as a parameter
Output: Printing each value to user
*/
void PrintEmpList(const Employee *EmpList){
	for (int i=0;i<3;i++){
		printf("%d %s %s %d\n", EmpList[i].id, EmpList[i].firstname, EmpList[i].lastname, EmpList[i].GPA);
	}
	
}

/*
Objective: Update the employee.dat file with user inputs
Input: Structure EmpList and EmpFile passed as parameters
Output: employee.dat is updated
*/
void SaveEmpList(const Employee *EmpList, FILE *EmpFile){
	for (int i=0;i<3;i++){
		fprintf(EmpFile, "%d %s %s %d\n", EmpList[i].id, EmpList[i].firstname, EmpList[i].lastname, EmpList[i].GPA);
	}
}










