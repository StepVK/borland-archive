//---------------------------------------------------------------------------
#include <windows.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <Math.h>
#define GL_PI 3.1415f
	GLfloat x,y,z,angle;
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
//---------------------------------------------------------------------------
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot,1,0,0);
	glRotatef(yRot,0,1,0);
	glBegin(GL_POINTS);
	z=-50.0f;
	for(angle=0;angle<=6*GL_PI;angle+=0.1f)
	{
		x=50*sin(angle);
		y=50*cos(angle);
		glVertex3f(x,y,z);
		z+=0.5f;
	}
	glEnd();
	glPopMatrix();
	glFlush();
}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key > 356.0f)
		xRot = 0.0f;

	if(key < -1.0f)
		xRot = 355.0f;

	if(key > 356.0f)
		yRot = 0.0f;

	if(key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
	}

void SetupRC(void)
{
	glClearColor(0.60f,0.40f,0.70f,0.1f);
	glColor3f(0,1,1);
}

void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat nRange = 100;
	if (h==0) {
		h=1;
	}
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w<=h) {
		glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,-nRange,nRange);
		}
		else
		glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,-nRange,nRange);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Points");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	SetupRC();
	glutMainLoop();
}
//---------------------------------------------------------------------------
