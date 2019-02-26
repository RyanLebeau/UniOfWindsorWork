#include <stdio.h>
#include <stdbool.h>

//void reassign(int *p, int*);
//void re2(int contents[], int);
void testit(int *, char[][12]);
void testit2(int *);
int main (void)
{
	char maze[12][12] = {{'1','1','1','1','1','1','1','1','1','1','1','1'},
						{'1','0','0','0','1','0','0','0','0','0','0','1'},
						{'0','0','1','0','1','0','1','1','1','1','0','1'},
						{'1','1','1','0','1','0','0','0','0','1','0','1'},
						{'1','0','0','0','0','1','1','1','0','1','0','0'},
						{'1','1','1','1','0','1','0','1','0','1','0','1'},
						{'1','0','0','1','0','1','0','1','0','1','0','1'},
						{'1','1','0','1','0','1','0','1','0','1','0','1'},
						{'1','0','0','0','0','0','0','0','0','1','0','1'},
						{'1','1','1','1','1','1','0','1','1','1','0','1'},
						{'1','0','0','0','0','0','0','1','0','0','0','1'},
						{'1','1','1','1','1','1','1','1','1','1','1','1'}};
	int *testptr, test = 0;
	testptr = &test;
	//maze[2][0] = 'X';
	testit(&test, maze);
	printf("%d %c", *testptr, maze[2][0]);
	/*
	int top=1;
	int num = 20;
	int contents[5]= {0,10,15,30,45};
	int *p;
	p = contents;
	
	reassign(p, &top);
	//re2(&top)
	printf("Value of list is %d\n", *(contents+top));
	*/
}

void testit(int *testptr, char maze[12][12]){
	*testptr = 1;
	maze[2][0] = 'X';
	testit2(*&testptr);
	
}

void testit2(int *testptr){
	*testptr = 2;
}
/*
void reassign(int *p, int *top)
{
	int test = 1;
	//*top += test;
	*(p+*top) = test;
	//re2(contents, *top);
	printf("%d", *(p+*top));
	return;
}

void re2(int contents[], int top)
{
	//int thing = **top;
	if (top== 2)
		printf("%d", contents[top]);
	else
		printf("nah");
	return;
}
*/