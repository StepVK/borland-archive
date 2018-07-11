//---------------------------------------------------------------------------

#pragma hdrstop

#include "Additional.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void DrawCube(GLfloat x,GLfloat y,GLfloat z,GLfloat size)


{
	GLfloat s=size/2;
	//oboznachim vershini
	/*
	A(x-s,y+s,z+s);
	B(x+s,y+s,z+s);
	C(x+s,y-s,z+s);
	D(x-s,y-s,z+s);
	A1(x-s,y+s,z-s);
	B1(x+s,y+s,z-s);
	C1(x+s,y-s,z-s);
	D1(x-s,y-s,z-s);
	*/
	glBegin(GL_QUADS);
		//1
		glVertex3f(x-s,y+s,z+s);
		glVertex3f(x-s,y-s,z+s);
		glVertex3f(x+s,y-s,z+s);
		glVertex3f(x+s,y+s,z+s);
		//2
		glVertex3f(x+s,y+s,z+s);
		glVertex3f(x+s,y-s,z+s);
		glVertex3f(x+s,y-s,z-s);
		glVertex3f(x+s,y+s,z-s);
		//3
		glVertex3f(x+s,y+s,z-s);
		glVertex3f(x+s,y-s,z-s);
		glVertex3f(x-s,y-s,z-s);
		glVertex3f(x-s,y+s,z-s);
		//4
		glVertex3f(x-s,y+s,z-s);
		glVertex3f(x-s,y-s,z-s);
		glVertex3f(x-s,y-s,z+s);
		glVertex3f(x-s,y+s,z+s);
		//5
		glVertex3f(x-s,y+s,z-s);
		glVertex3f(x-s,y+s,z+s);
		glVertex3f(x+s,y+s,z+s);
		glVertex3f(x+s,y+s,z-s);
		//6
		glVertex3f(x-s,y-s,z+s);
		glVertex3f(x-s,y-s,z-s);
		glVertex3f(x+s,y-s,z-s);
		glVertex3f(x+s,y-s,z+s);
	glEnd();
}

//naglo spizgheno
void DrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
    {
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
	GLfloat ds = 1.0f / (GLfloat) iSlices;
	GLfloat dt = 1.0f / (GLfloat) iStacks;
	GLfloat t = 1.0f;	
	GLfloat s = 0.0f;
    GLint i, j;     // Looping variables

	for (i = 0; i < iStacks; i++) 
		{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));

        // Many sources of OpenGL sphere drawing code uses a triangle fan
        // for the caps of the sphere. This however introduces texturing 
        // artifacts at the poles on some OpenGL implementations
		glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
		for ( j = 0; j <= iSlices; j++) 
			{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));

			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;
            
            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);

            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
            }
        glEnd();

        t -= dt;
        }

}
//end of Naglo spizgheno