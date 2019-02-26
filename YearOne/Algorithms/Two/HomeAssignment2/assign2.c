/*
Ryan Lebeau
12/02/2017
assign2.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//function declarations
void printMaze(char[][12]);
int findStart(char[][12]);
int mazeTraverse(char[][12], int, int, int);
int coordsAreEdge(int);
int validMove(char[][12], int, int);

/*
Objective: Main program function, handles openening of inputs and calls functions
Input: None
Output: Returns 0
*/
int main(void){
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
	int xPos,yPos, direction = 2;
	
	//check to make sure there is an exit
	bool exit = false;
	for (int i=0; i<12; i++){
		if (maze[i][11]=='0')
			exit = true;
	}
	//if no exit then tell user and finish program
	if (!exit){
		printf("This maze has no exit.");
		return 0;
	}
	yPos = findStart(maze);
	mazeTraverse(maze, xPos, yPos, direction);
	return 0;
	
}

/*
Objective: Print the 2D maze to the user
Input: 2D array 'maze'
Output: prints each element of 'maze' and returns 0
*/
void printMaze(char maze[12][12]){
	//loop to access every element
	for (int i=0; i<12; i++){
		for (int j=0; j<12; j++){
			printf("%*c", 2, maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
Objective: Find the starting point of the maze
Input: 2D array 'maze'
Output: Returns position of start point
*/
int findStart(char maze[12][12]){
	for (int i=0; i<12; i++){
		if (maze[i][0] == '0')
			return i;
	}
}

//global variable to handle if moving backwards or not
int xBack = 0;
/*
Objective: Traverse through the maze from start to exit using recursion
Input: 2D array 'maze', the current coordinates, and direction being faced
Output: Calls validMove, printMaze, coordsAreEdge, and returns 0
*/
int mazeTraverse(char maze[12][12], int xPos, int yPos, int direction){
	maze[yPos][xPos] = 'X';
	//switch case that determines which way to move depending on direction facing
	switch(direction){
		//N=1, E=2, S=3, W=4
		//if facing east
		case 2:
			//right
			if (validMove(maze, xPos, yPos+1)){
				yPos++;
				direction = 3;
			}
			//forward
			else if (validMove(maze, xPos+1, yPos)){
				xPos++;
			}
			//left
			else if (validMove(maze, xPos, yPos-1)){
				yPos--;
				direction = 1;
			}
			//backwards
			else if (validMove(maze, xPos-1, yPos)){
				xPos--;
				direction = 4;
			}
			//back for 'X's
			else{
				xBack = 1;
				xPos--;
				//direction = 4;
			}
			break;
		//if facing north
		case 1:
			//right
			if (validMove(maze, xPos+1, yPos)){
				xPos++;
				direction = 2;
			}
			//forward
			else if (validMove(maze, xPos, yPos-1)){
				yPos--;
			}
			//left
			else if (validMove(maze, xPos-1, yPos)){
				xPos--;
				direction = 4;
			}
			//backwards
			else if (validMove(maze, xPos, yPos+1)){
				yPos++;
				direction = 3;
			}
			//back for 'X's
			else{
				xBack = 1;
				yPos++;
				//direction = 3;
			}
			break;
		//if facing south
		case 3:
			//right
			if (validMove(maze, xPos-1, yPos)){
				xPos--;
				direction = 4;
			}
			//forward
			else if (validMove(maze, xPos, yPos+1)){
				yPos++;
			}
			//left
			else if (validMove(maze, xPos+1, yPos)){
				xPos++;
				direction = 2;
			}
			//backwards
			else if (validMove(maze, xPos, yPos-1)){
				yPos--;
				direction = 1;
			}
			//back for 'X's
			else{
				xBack = 1;
				yPos--;
				//direction = 1;
			}
			break;
		//if facing west
		case 4:
			//right
			if (validMove(maze, xPos, yPos-1)){
				yPos--;
				direction = 1;
			}
			//forward
			else if (validMove(maze, xPos-1, yPos)){
				xPos--;
			}
			//left
			else if (validMove(maze, xPos, yPos+1)){
				yPos++;
				direction = 3;
			}
			//backwards
			else if (validMove(maze, xPos+1, yPos)){
				xPos++;
				direction = 2;
			}
			//back for 'X's
			else{
				xBack = 1;
				xPos++;
			}
			break;
	}
	//check if curretn position is exit
	if (coordsAreEdge(xPos)){
		maze[yPos][xPos] = 'X';
		printMaze(maze);
		return 0;
	}
	//if not recursively calls the function
	else{
		printMaze(maze);
		printf("Press enter to see next move.\n");
		//registering when user presses enter
		/*
		char enter = 0;
		while(enter != '\n')
			enter = getchar();
		*/
		mazeTraverse(maze, xPos, yPos, direction);
		
	}
}

/*
Objective: Check if a move can be done or not
Input: 2D array 'maze' and current position
Output: Returns 1 if move is valid and returns 0 if not
*/
int validMove(char maze[12][12], int xPos, int yPos){
	if (maze[yPos][xPos]=='0'){
		xBack = 0;
		return 1;
	}
	//if moving backwards through X's and not only '0's
	else if(xBack==1 && maze[yPos][xPos]=='X')
		return 1;
	else
		return 0;
	
}

/*
Objective: To check if current position is on edge of maze (exit) 
Input: Current x position
Output: Returns 1 if x position is in the last column, 0 if not
*/
int coordsAreEdge(int xPos){
	if (xPos == 11)
		return 1;
	else{
		return 0;
	}
}





