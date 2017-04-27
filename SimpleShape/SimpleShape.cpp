#pragma comment(lib,"glut\\glut32.lib")
#include <stdlib.h>
#include "glut\glut.h"

float clr;
void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
}

void figure()
{

	glFrontFace(GL_CW);

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1, 0, 1);
	glVertex3f(200.0f, 150.0f, 0.0f);
	glColor3f(0, 0.8, 1);
	glVertex3f(120.0f, 300.0f, 0.0f);
	glColor3f(0, 0, 0.5);
	glVertex3f(300.0f, 300.0f, 0.0f);
	glColor3f(0, 0, 1);
	glVertex3f(200.0f, 450.0f, 0.0f);
	glColor3f(0, 0.8, 1);
	glVertex3f(400.0f, 450.0f, 0.0f);
	glColor3f(0, 0, 0.5);
	glVertex3f(300.0f, 300.0f, 0.0f);
	glColor3f(0, 0, 1);
	glVertex3f(480.0f, 300.0f, 0.0f);
	glColor3f(0, 0, 1);
	glVertex3f(400.0f, 150.0f, 0.0f);
	glColor3f(0, 0, 0.5);
	glVertex3f(300.0f, 300.0f, 0.0f);
	glColor3f(0, 0.8, 1);
	glVertex3f(200.0f, 150.0f, 0.0f);
	glEnd();
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	figure();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Simple Shape task");
	init2D(0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display);
	glutMainLoop();
}