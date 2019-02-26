/*
Ryan Lebeau
08/11/2016
pinCode.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	//creating the needed variables
	int numStud, GPAFreq[4]={0}, randGPA;
	
	//prompting the user for the number of students
	printf("Enter the number of students: ");
	scanf("%d", &numStud);
	//creating a dynamic start point for random
	srand(time(NULL));
	//a loop that creates inputs and sorts them for the number of students
	for (int i=1;i<=numStud;i++){
		//creating a random number between 1 and 4
		randGPA = rand()%6;
		//if the gpa is invalid out put that it's invalid
		if (randGPA<=4 && randGPA>=1){
			printf("GPA of student #%d is: %d\n", i, randGPA);
			//switch case to add to each counted possible GPA
			switch(randGPA){
				case 1:
					GPAFreq[0]++;
					break;
				case 2:
					GPAFreq[1]++;
					break;
				case 3:
					GPAFreq[2]++;
					break;
				case 4:
					GPAFreq[3]++;
					break;
			}
		}
		//output the student and their gpa
		else{
			printf("GPA of student #%d is: %d\n", i, randGPA);
			printf("Invalid GPA\n");
			i--;
		}
	}

	//outputting how many students have had each specific GPA
	printf("\n");
	printf("The total number of students is %d.\n", numStud);
	printf("GPA 1 --- %d student(s)\n", GPAFreq[0]);
	printf("GPA 2 --- %d student(s)\n", GPAFreq[1]);
	printf("GPA 3 --- %d student(s)\n", GPAFreq[2]);
	printf("GPA 4 --- %d student(s)\n", GPAFreq[3]);
	
}