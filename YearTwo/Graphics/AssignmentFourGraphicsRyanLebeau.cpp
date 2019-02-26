/*
Ryan Lebeau
22/03/2018
Intro to Graphics
AssignmentFourGraphicsRyanLebeau.cpp
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
bool redL = true, blueL = true, mainL = true;


int main(int argc, char* argv[]) {
	init(&argc, argv);
	//displaying window
	glutDisplayFunc(myDraw);
	//right click menu
	glutCreateMenu(rcMenu);
	glutAddMenuEntry("Z Inc", 1);
	glutAddMenuEntry("Z Dec", 2);
	glutAddMenuEntry("RedLight Toggle", 3);
	glutAddMenuEntry("BlueLight Toggle", 4);
	glutAddMenuEntry("MainLight Toggle", 5);
	glutAddMenuEntry("Quit", 6);
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
		lookX = x-5;
		lookY = y-5;
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
		//glNormal3f(0.0f, 0.0f, 0.0f);
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

void assignFourLandscape() {
	//darkGreen - grass
	glColor3d(0.33f, 0.4196f, 0.184f);
	glBegin(GL_POLYGON);
		glVertex3f(-4.0f, -1.01f, 4.0f);
		glVertex3f(3.0f, -1.01f, 4.0f);
		glVertex3f(3.0f, -1.01f, -4.0f);
		glVertex3f(-4.0f, -1.01f, -4.0f);
	glEnd();
	//light post red
	glColor3d(0.86f, 0.07f, 0.23f);
	glBegin(GL_POLYGON);
		glVertex3f(3.0f, -1.0f, 4.0f);
		glVertex3f(3.0f, 0.0f, 4.0f);
		glVertex3f(3.0f, 0.0f, 3.9f);
		glVertex3f(3.0f, -1.0f, 3.9f);
	glEnd();
	//light post blue
	glColor3d(0.25f, 0.41f, 0.88f);
	glBegin(GL_POLYGON);
		glVertex3f(3.0f, -1.0f, -3.9f);
		glVertex3f(3.0f, 0.0f, -3.9f);
		glVertex3f(3.0f, 0.0f, -4.0f);
		glVertex3f(3.0f, -1.0f, -4.0f);
	glEnd();
	//grey - walkway
	glColor3d(0.662f, 0.662f, 0.662f);
	glBegin(GL_POLYGON);
		glVertex3f(1.0f, -0.99f, 0.5f);
		glVertex3f(3.0f, -0.99f, 0.5f);
		glVertex3f(3.0f, -0.99f, -0.5f);
		glVertex3f(1.0f, -0.99f, -0.5f);
	glEnd();
	//darkGrey - road
	glColor3d(0.333f, 0.333f, 0.333f);
	glBegin(GL_POLYGON);
		glVertex3f(3.0f, -1.0f, 6.0f);
		glVertex3f(5.0f, -1.0f, 6.0f);
		glVertex3f(5.0f, -1.0f, -6.0f);
		glVertex3f(3.0f, -1.0f, -6.0f);
	glEnd();
}

//caller function to draw
void myDraw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0f, 640 / 480, 1.0f, 25.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(lookX, lookY, lookZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//enable lighting
	glEnable(GL_LIGHTING);
	if (redL) { glEnable(GL_LIGHT0); }
	else { glDisable(GL_LIGHT0); }
	if (blueL) { glEnable(GL_LIGHT1); }
	else { glDisable(GL_LIGHT1); }
	if (mainL) { glEnable(GL_LIGHT2); }
	else { glDisable(GL_LIGHT2); }
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	//light 0 - red - positional
	GLfloat colourLight0[] = { 0.7f,0.2f,0.2f,1.0f };
	GLfloat posLight0[] = { 3.0f,0.0f,3.95f,1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, colourLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
	//light 1 - blue - positional
	GLfloat colourLight1[] = { 0.2f,0.2f,0.9f,1.0f };
	GLfloat posLight1[] = { 3.0f,0.0f,-3.95f,1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, colourLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, posLight1);
	//light 2 - directional
	GLfloat colourLight2[] = { 0.6f,0.6f,0.6f,1.0f };
	GLfloat posLight2[] = { -5.0f,0.0f,3.0f,0.0f };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, colourLight2);
	glLightfv(GL_LIGHT2, GL_POSITION, posLight2);

	houseDraw();
	windowDoor();
	assignFourLandscape();
	glutSwapBuffers();
}

//right click menu
void rcMenu(int choice) {
	switch (choice) {
	//z inc
	case 1:
		lookZ += 2.0f; break;
	//z dec
	case 2:
		lookZ -= 2.0f; break;
	//red light toggle
	case 3:
		redL = !redL; break;
	//blue light toggle
	case 4:
		blueL = !blueL; break;
	//main light toggle
	case 5:
		mainL = !mainL; break;
	//exit
	case 6:
		exit(0);
		break;
	}
	myDraw();
}


