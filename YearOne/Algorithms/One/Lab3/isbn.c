#include <stdio.h>
int main(void)
{
	char barNum;
	int checkNumber;
	printf("Enter the first nine digits of ISBN: ");
	scanf("%[^\n]s", &barNum);
	//checkNumber = (11-(((barNum[0]*9)+(barNum[1]*8)(barNum[2]*7)+(barNum[3]*6)+(barNum[4]*5)+(barNum[5]*4)+(barNum[6]*3)+(barNum[7]*2))%11)); 
	printf("Check digit: %i", barNum[1]);
}