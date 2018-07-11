//---------------------------------------------------------------------------
#include <windows.h>
#include <gl/glut.h>
#include <gl/glu.h>

//---------------------------------------------------------------------------
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSolidTeapot(10);
	glFlush();
}

void SetupRC(void)
{
	glClearColor(0.60f,0.40f,0.70f,0.1f);
}

 void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Simple");
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}
//---------------------------------------------------------------------------
