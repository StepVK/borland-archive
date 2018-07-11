//---------------------------------------------------------------------------
#include <windows.h>
#include <gl/glut.h>
#include <gl/glu.h>
GLfloat x1=0,y1=0,rsize=25,xstep=1,ystep=1,windowWidth,windowHeight;

//---------------------------------------------------------------------------
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,1);
	glRectf(x1,y1,x1+rsize,y1-rsize);
	glutSwapBuffers();
}

void TimerFunction(int value)
{
	if (x1>windowWidth-rsize || x1<-windowWidth) {
		xstep=-xstep;
	}
	if (y1>windowHeight || y1 < -windowHeight + rsize) {
		ystep=-ystep;
	}
	x1+=xstep;
	y1+=ystep;
	if (x1>(windowWidth-rsize+xstep)) {
		x1=windowWidth-rsize-1;
	}
	else if (x1<-(windowWidth+xstep)) {
			 x1=-windowWidth-1;
		 }
	if (y1>(windowHeight+ystep)) {
		y1=windowHeight+1;
	}
	else if (y1< -(windowHeight-rsize+ystep)) {
			 y1=-windowHeight+rsize-1;
		 }
	glutPostRedisplay();
	glutTimerFunc(33,TimerFunction,1);
}

void SetupRC(void)
{
	glClearColor(0.6,0.4,0.7,0.1);
}

void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspectRatio;
	if (h==0) {
		h=1;
	}
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w<=h) {
		windowWidth=100;
		windowHeight=100/aspectRatio;
		glOrtho(-100,100,-windowHeight,windowHeight,1,-1);
		}
	else {
		windowWidth=100*aspectRatio;
		windowHeight=100;
		glOrtho(-windowWidth,windowWidth,-100,100,1,-1);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

 void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Bounce");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunction,1);
	SetupRC();
	glutMainLoop();
}
//---------------------------------------------------------------------------
