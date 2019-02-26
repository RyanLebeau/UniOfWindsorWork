/*
Ryan Lebeau
16/03/2018
Intro to Graphics
AssignmentThreeGraphicsRyanLebeau.cpp
*/
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

void init(int*, char**);
void houseDraw();
void OnMouseClick(int,int,int,int);
void myDraw();
void rcMenu(int);

float lookX = 0.0f, lookY = 0.0f, lookZ = 4.0f, fX, fY, fZ=-1.0f;


int main(int argc, char* argv[]) {
	init(&argc, argv);
	//displaying window
	glutDisplayFunc(myDraw);
	//right click menu
	glutCreateMenu(rcMenu);
	glutAddMenuEntry("Z Inc", 1);
	glutAddMenuEntry("Z Dec", 2);
	glutAddMenuEntry("Quit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//linking left mouse click
	glutMouseFunc(OnMouseClick);

	glutMainLoop();
	//return 1;
}

void init(int* argc, char** argv) {
	//initialize GLUT
	glutInit(argc, argv);
	//set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//set the window size
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D House - AssignThree 104535367");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
}

//on left mouse click
void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x /= 50;
		y /= 50;
		lookX = x;
		lookY = y;
		myDraw();
	}
}

//wheel drawing function
void houseDraw() {
	//red - front roof
	glColor3d(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0f, 3.0f, 0.0f);
		glVertex3f(1.0f, 3.0f, 0.0f);
		glVertex3f(1.0f, 0.5f, 1.25f);
		glVertex3f(-1.0f, 0.5f, 1.25f);
	glEnd();
	//redBrown- back roof
	glColor3d(0.65f, 0.1f, 0.15f);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0f, 3.0f, 0.0f);
		glVertex3f(1.0f, 3.0f, 0.0f);
		glVertex3f(1.0f, 0.5f, -1.25f);
		glVertex3f(-1.0f, 0.5f, -1.25f);
	glEnd();
	//brown - front
	glColor3d(0.6f, 0.3f, 0.2f);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	//green - back
	glColor3d(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
	//blue - top
	glColor3d(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	//yellow - bottom
	glColor3d(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
	//purple - right
	glColor3d(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	//pink - right top
	glColor3d(0.94f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 3.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	//teal - left
	glColor3d(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
	//grey - left top
	glColor3d(0.7f, 0.77f, 0.87f);
	glBegin(GL_POLYGON);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 3.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
}

void windowDoor() {
	//black - door (puprle side)
	glColor3d(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(1.01f, -1.0f, 0.25f);
		glVertex3f(1.01f, 0.15f, 0.25f);
		glVertex3f(1.01f, 0.15f, -0.25f);
		glVertex3f(1.01f, -1.0f, -0.25f);
	glEnd();
	//white - door handle
	glColor3d(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3f(1.02f, -0.5f, -0.1f);
		glVertex3f(1.02f, -0.4f, -0.1f);
		glVertex3f(1.02f, -0.4f, -0.15f);
		glVertex3f(1.02f, -0.5f, -0.15f);
	glEnd();
	//grey - window frame
	glColor3d(0.86f, 0.86f, 0.86f);
	glBegin(GL_POLYGON);
		glVertex3f(1.01f, 0.6f, 0.55f);
		glVertex3f(1.01f, 1.4f, 0.55f);
		glVertex3f(1.01f, 1.4f, -0.55f);
		glVertex3f(1.01f, 0.6f, -0.55f);
	glEnd();
	//skyBlue - window
	glColor3d(0.0f, 0.55f, 0.55f);
	glBegin(GL_POLYGON);
		glVertex3f(1.02f, 0.7f, 0.5f);
		glVertex3f(1.02f, 1.3f, 0.5f);
		glVertex3f(1.02f, 1.3f, -0.5f);
		glVertex3f(1.02f, 0.7f, -0.5f);
	glEnd();
}

/* assign4 stuff
void backyard() {
	//green - grass
	glColor3d(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-3.0f, -1.0f, 1.0f);
		glVertex3f(0.0f, -1.0f, 1.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(-3.0f, -1.0f, -1.0f);
	glEnd();
	
	while (fZ <= 1.0) {
		glColor3d(0.83f, 0.83f, 0.83f);
		glBegin(GL_POLYGON);
			glVertex3f(-3.0f, -1.0f, fZ+=0.1f);
			glVertex3f(-3.0f, -0.3f, fZ+=0.1f);
			glVertex3f(-3.0f, -0.3f, fZ);
			glVertex3f(-3.0f, -1.0f, fZ);
		glEnd();
		fZ += 0.3f;
	}

	//grey - fence post
}*/

//caller function to draw
void myDraw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0f, 640 / 480, 1.0f, 25.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(lookX, lookY, lookZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	houseDraw();
	windowDoor();
	//backyard();
	glutSwapBuffers();
}

//right click menu
void rcMenu(int choice) {
	switch (choice) {
	//z inc
	case 1:
		lookZ += 1.0f; break;
	//z dec
	case 2:
		lookZ -= 1.0f; break;
	//exit
	case 3:
		exit(0);
		break;
	}
	myDraw();
}


