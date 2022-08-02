/*
 *  shadow.c
 *  This program draws a polygon and its shadow.
 */


#include <stdlib.h>           
#ifdef __APPLE__
#include <GLUT/glut.h>              /* glut.h */
#else
#include <GL/glut.h>
#endif

   GLfloat theta=0.0;

void display(void)

{
/* set clear color to white and clear window */

	GLfloat light[3]={0.0, 10.0, 0.0};
	GLfloat m[16];

	double sin(), cos();

	int i;
	for(i=0;i<16;i++) m[i]=0.0;

	light[0]=10.0*sin((6.28/180.0)*theta);
	light[2]=10.0*cos((6.28/180.0)*theta);
	m[0]=m[5]=m[10]=1.0;
	m[7]=-1.0/light[1];
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

/* set drawing/fill  color to red */

	glColor3f(1.0, 0.0, 0.0);

/* set up standard orthogonal view with clipping */
/* box as cube of side 2 centered at origin */

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -5.0, 5.0); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

/* define unit square polygon */

	glBegin(GL_POLYGON);
	 	glVertex3f(-0.5, 0.5, -0.5);
	 	glVertex3f(-0.5, 0.5, 0.5);
	 	glVertex3f(0.5, 0.5, 0.5);
	 	glVertex3f(0.5, 0.5, -0.5);
	glEnd();

	glPushMatrix();
	glTranslatef(light[0], light[1],light[2]);
	glMultMatrixf(m);
	glTranslatef(-light[0], -light[1],-light[2]);
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	 	glVertex3f(-0.5, 0.5, -0.5);
	 	glVertex3f(-0.5, 0.5, 0.5);
	 	glVertex3f(0.5, 0.5, 0.5);
	 	glVertex3f(0.5, 0.5, -0.5);
	glEnd();
	glPopMatrix();

/* Swap buffers */

	glutSwapBuffers();

}

void myidle()
{
   theta+=2.0;
   if(theta>360.0) theta-=360;
   glutPostRedisplay();
}

int main(int argc, char** argv)
{

/* Initialize mode and open a window in upper left corner of screen */
/* Window title is name of program (arg[0]) */

	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH); 
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("shadow");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutIdleFunc(myidle);
	glutMainLoop();

}
