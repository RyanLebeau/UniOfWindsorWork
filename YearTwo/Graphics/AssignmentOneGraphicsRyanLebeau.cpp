/*
Ryan Lebeau
02/02/2018
Intro to Graphics
AssignmentOneGraphicsRyanLebeau.cpp
*/
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>


int x0, x1, Y0, Y1;

//rendering in the window
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250, -250, 250);
	glColor3f(255, 255, 255);
	glPointSize(1);
}

//drawing a pixel
void setPixel(int x, int y)
{ 
	glBegin(GL_POINTS);
	//set pixel coordinates
	glVertex2i(x, y);  
	glEnd();
}

//line drawing algorithm
void BresenhamsLineAlgorithm(int x0, int y0, int x1, int y1) {
	//calculating the delta x and y
	int dx = x1 - x0;
	int dy = y1 - y0;
	int y = y0, x = x0;
	int xi=1, yi=1, i0, i1, error;
	//altering the delta's to accomodate for lines in different quadrants
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	if (x1 < x0) xi = -1;
	if (y1 < y0) yi = -1;

	//drawing the line
	if (dx > dy) {
		setPixel(x, y);
		i0 = 2 * (dy - dx);
		i1 = 2 * dy;
		error = 2 * dy - dx;
		//each pixel of the line
		for (int i = 0;i < dx;i++) {
			if (error >= 0) {
				y += yi;
				error += i0;
			}
			else
				error += i1;
			x += xi;
			setPixel(x, y);
		}
	}
	else {
		setPixel(x, y);
		i0 = 2 * (dx - dy);
		i1 = 2 * dx;
		error = 2 * dx - dy;
		for (int i = 0;i < dy;i++) {
			if (error >= 0) {
				x += xi;
				error += i0;
			}
			else
				error += i1;
			y += yi;
			setPixel(x, y);
		}
	}

	
}

//caller function for the line algorithm
void myDraw() {
	BresenhamsLineAlgorithm(x0, Y0, x1, Y1);
	glFlush();
}

int main(int argc, char* argv[]) {
	//user entered line coordinates
	std::cout << "Enter both end points of the line(each seperated by a space):";
	scanf_s("%d %d %d %d", &x0, &Y0, &x1, &Y1);
	//initialize GLUT
	glutInit(&argc, argv);
	//set up some memory buffers for our display
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	//set the window size
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	//create the window with a title
	glutCreateWindow("Bresenham's Line Algorithm - AssignOne 104535367");
	//creating the window and drawing the entered line
	render();
	glutDisplayFunc(myDraw);
	glutMainLoop();

}
