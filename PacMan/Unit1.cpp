#include <windows.h>
#include <math.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "Additional.h"
/*
class PacMan
{
	public:
	int Size;
	bool Rage;
	int Color;
	GLfloat PosX,PosY,PosZ;
	void Draw();
	PacMan(int Col,GLfloat x,GLfloat y, GLfloat z,int Size);

};

PacMan::PacMan(int Col,GLfloat x,GLfloat y, GLfloat z,int Size)
{
	this->Size=Size;
	this->Rage=0;
	this->Color=Col;
	PosX=x;
	PosY=y;
	PosZ=z;

}


PacMan PM(1,0,0,0,10);
*/
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
int sizeofquad=10;

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
		glRotatef(xRot,1,0,0);
		glRotatef(yRot,0,1,0);
		glColor3f(1,0,0);
		DrawCube(0,0,0,sizeofquad);
		glPushMatrix();
			glColor3f(0,1,0);
			glTranslatef(sizeofquad/4,sizeofquad/4,sizeofquad/2);
			glutSolidSphere(sizeofquad/10,100,200);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0,0,1);
			glTranslatef(-sizeofquad/4,sizeofquad/4,sizeofquad/2);
			glutSolidSphere(sizeofquad/10,100,200);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(0,0,0,1);
	glShadeModel(GL_FLAT);
}

void KeysFunc(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key == GLUT_KEY_PAGE_UP)
    	sizeofquad += 10;

	if(xRot > 356.0f)
		xRot = 0.0f;

	if(xRot < -1.0f)
		xRot = 355.0f;

	if(yRot > 356.0f)
		yRot = 0.0f;

	if(yRot < -1.0f)
		yRot = 355.0f;
		
	 glutPostRedisplay();
}

void ChangeSize(int w,int h)
{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("PacBro");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeysFunc);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
