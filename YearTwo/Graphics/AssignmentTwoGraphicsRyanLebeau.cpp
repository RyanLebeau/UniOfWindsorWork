/*
Ryan Lebeau
14/02/2018
Intro to Graphics
AssignmentTwoGraphicsRyanLebeau.cpp
*/
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>


float wheelX = 10.0f, wheelY = 250.0f, backX = 0.0f, backY = 255.0f, pos = 0.0f, ROC = 1.0f;
bool leftClick = false;

//rendering in the window
void render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glPointSize(1);
}

//right click menu
void rcMenu(int choice) {
	switch (choice) {
	//speed up
	case 1:
		if (ROC >= 0) { ROC += 1; }
		else { ROC -= 1; }
		break;
	//slow down
	case 2:
		if (ROC >= 0) { if (ROC != 0) { ROC -= 1; } }
		else { ROC += 1; }
		break;
	//change direction
	case 3:
		ROC *= -1;
		break;
	//exit
	case 4:
		exit(0);
		break;
	}
}

//on mouse clicks
void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!leftClick) { leftClick = true; }
		else { leftClick = false; }
	}
}

//wheel drawing function
void wheelDraw(float x, float y) {
	glColor3d(0, 0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, 0);
		glVertex3f(x + 5, y + 10, 0);
		glVertex3f(x + 15, y + 10, 0);
		glVertex3f(x + 20, y, 0);
		glVertex3f(x + 15, y - 10, 0);
		glVertex3f(x + 5, y - 10, 0);
	glEnd();
}

//drawing the main components of the truck
void truckDraw() {
	glColor3d(0, 0, 1);
	//truck back
	glBegin(GL_POLYGON);
		glVertex3f(backX, backY, 0);
		glVertex3f(backX, backY + 65, 0);
		glVertex3f(backX + 125, backY + 65, 0);
		glVertex3f(backX + 125, backY, 0);
	glEnd();
	//connection between box and cab
	glColor3d(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
		glVertex3f(backX + 125, backY + 5, 0);
		glVertex3f(backX + 125, backY + 10, 0);
		glVertex3f(backX + 140, backY + 10, 0);
		glVertex3f(backX + 140, backY + 5, 0);
	glEnd();
	//truck cab base
	glColor3d(0, 0.5f, 0.7f);
	glBegin(GL_POLYGON);
		glVertex3f(backX + 140, backY, 0);
		glVertex3f(backX + 140, backY + 55, 0);
		glVertex3f(backX + 190, backY + 55, 0);
		glVertex3f(backX + 190, backY, 0);
	glEnd();
	//truck cab windsheild
	glColor3d(1, 1, 1);
	glBegin(GL_POLYGON);
		glVertex3f(backX + 165, backY + 40, 0);
		glVertex3f(backX + 165, backY + 52, 0);
		glVertex3f(backX + 187, backY + 52, 0);
		glVertex3f(backX + 187, backY + 30, 0);
	glEnd();
	//truck cab door
	glColor3d(1, 0, 0);
	glBegin(GL_POLYGON);
		glVertex3f(backX + 172, backY + 8, 0);
		glVertex3f(backX + 172, backY + 33, 0);
		glVertex3f(backX + 187, backY + 27, 0);
		glVertex3f(backX + 187, backY + 8, 0);
	glEnd();
	
}


//caller function to draw
void myDraw() {
	//rest of truck
	truckDraw();
	//left most wheel
	wheelDraw(wheelX, wheelY);
	//middle wheel
	wheelDraw(wheelX+75, wheelY);
	//right most wheel
	wheelDraw(wheelX + 150, wheelY);
	glFlush();
}

//moving the truck
void drive(int data) {
	//if truck is not stopped
	if (!leftClick) {
		//every 30milliseconds trigger the timer
		glutTimerFunc(30, drive, -1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glTranslatef(ROC, 0.0f, 0.0f);
		pos += ROC;
		//if truck is off screen and moving forward
		if (pos >= 500 && ROC>=0) {
			glTranslatef(-700.0f, 0.0f, 0.0f);
			pos = -200;
		}
		//if truck is off screen and moving backwards
		else if (pos < -200 && ROC < 0) {
			glTranslatef(700.0f, 0.0f, 0.0f);
			pos = 500;
		}
		glutPostRedisplay();
	}
	//if truck is stopped
	else {
		glutTimerFunc(30, drive, -1);
	}
}

int main(int argc, char* argv[]) {
	//initialize GLUT
	glutInit(&argc, argv);
	//set up some memory buffers for our display
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
	//set the window size
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	//create the window with a title
	glutCreateWindow("Truck Driver - AssignTwo 104535367");
	//creating the window
	render();
	//right click menu
	glutCreateMenu(rcMenu);
	glutAddMenuEntry("Speed Up", 1);
	glutAddMenuEntry("Slow Down", 2);
	glutAddMenuEntry("Change Direction", 3);
	glutAddMenuEntry("Quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//displaying truck
	glutDisplayFunc(&myDraw);
	//linking left mouse click
	glutMouseFunc(OnMouseClick);
	//triggering truck drive
	glutTimerFunc(30, drive, -1);

	glutMainLoop();
	return 1;
}
