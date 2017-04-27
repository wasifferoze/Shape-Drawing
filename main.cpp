#pragma comment(lib,"glut\\glut32.lib")
#include <stdlib.h>
#include "glut\glut.h"

#include "Polygon.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<Shapes::Polygon*> Polygons;
Shapes::Polygon * currentPolygon;


void InitializeScene(){
	glClearColor(1.0,1.0,1.0,1.0);	
	glMatrixMode (GL_PROJECTION);
}
void WindowsSizeChangedEvent(int w, int h){
{

		GLfloat nRange = 100.0f;


		if(h == 0)
			h = 1;

		glViewport(0, 0, w, h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (w <= h) 
			glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
		else 
			glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}
void MouseEvent(int button,int state,int x,int y){

	double worldX=0, worldY=0, worldZ=0;


	GLint view[4];//viewport dimensions+pos
	GLdouble  projMatrix[16];//projection matrix
	GLdouble  modelMatrix[16];

	glGetDoublev (GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev (GL_PROJECTION_MATRIX,projMatrix);
	glGetIntegerv( GL_VIEWPORT, view );

	gluUnProject(x,view[3]-y,0.5,modelMatrix,projMatrix,view, &worldX, &worldY, &worldZ);


	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		glutDetachMenu(GLUT_RIGHT_BUTTON);

		currentPolygon->addVertex(worldX,worldY);


	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		currentPolygon->finishPolygon();
		Polygons.push_back(currentPolygon);
		currentPolygon=new Shapes::Polygon();
	}

	glutPostRedisplay();

}
void RenderGrid(int distance){


	glEnable(GL_POLYGON_STIPPLE);
	glColor3ub(64,64,64);
	for(int i=-400;i<=400;i+=distance){
		glBegin(GL_LINES);
		glVertex2i(i,-300);
		glVertex2i(i,300);
		glEnd();
	}
	for(int i=-300;i<=300;i+=distance){
		glBegin(GL_LINES);
		glVertex2i(-400, i);
		glVertex2i(400,i);
		glEnd();
	}
	glDisable(GL_POLYGON_STIPPLE);

}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(6);
	using namespace Shapes;

	RenderGrid(5);

	
	if(currentPolygon){
		currentPolygon->Render();
	}

	for(int i=0;i<Polygons.size();i++)
	{
		Polygons[i]->Render();
	}


	glFlush();
}
void menu(int value){

	switch(value){
	case 1: //black
		currentPolygon->setColor(0,0,0);

		break;
	case 2://gray
		currentPolygon->setColor(128,128,128);
		break;
	case 3:		//red
		currentPolygon->setColor(255,0,0);
		break;
	case 4: //green
		currentPolygon->setColor(0,255,0);
		break;
	case 5: //blue
		currentPolygon->setColor(0,0,255);
		break;
	case 6: //orange
		currentPolygon->setColor(252, 188,103);
		break;
	case 7: //yellow
		currentPolygon->setColor(255, 255,0);
		break;
	}

	glutDetachMenu(GLUT_RIGHT_BUTTON);

}

int main(int argc, char* argv[])
{	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Wasif Feroze(201624060192)'s Shape Drawing Program");
	glutReshapeFunc(WindowsSizeChangedEvent);
	glutMouseFunc(MouseEvent);
	InitializeScene();



	int colorMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Black", 1);
	glutAddMenuEntry("Gray", 2);
	glutAddMenuEntry("Red", 3);
	glutAddMenuEntry("Green", 4);
	glutAddMenuEntry("Blue", 5);
	glutAddMenuEntry("Orange", 6);
	glutAddMenuEntry("Yellow", 7);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	currentPolygon=new Shapes::Polygon();


	glutDisplayFunc(RenderScene);

	glutMainLoop();


	return 0;
}