
/* Shaded teapot using Bezier surfaces */

#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef GLfloat point[3];


point data[32][4][4];

/* 306 vertices */

#include "vertices.h"

/* 32 patches each defined by 16 vertices, arranged in a 4 x 4 array */
/* NOTE: numbering scheme for teapot has vertices labeled from 1 to 306 */
/* remnent of the days of FORTRAN */

#include "patches.h"

void display(void)
{
   int i, j, k;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);


	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0); 
 	glRotatef(-35.26, 1.0, 0.0, 0.0);
	glRotatef(-45.0, 0.0, 1.0, 0.0);  

	/* gluLookAt(-1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); */

/* data aligned along z axis, rotate to align with y axis */

    glRotatef(-90.0, 1.0,0.0, 0.0); 
    for(k=0;k<32;k++) 
	{
       glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &data[k][0][0][0]);
       for (j = 0; j <= 8; j++) 
	   {
            glBegin(GL_LINE_STRIP);
            for (i = 0; i <= 30; i++)
               glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
            glEnd();
            glBegin(GL_LINE_STRIP);
            for (i = 0; i <= 30; i++)
               glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
            glEnd();
        }
   }
   glFlush();
}
void
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
            4.0 * (GLfloat) h / (GLfloat) w, -20.0, 20.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    display();
}

void myinit()
{
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);

}

main(int argc, char *argv[])
{
int i,j, k, m, n;



    for(i=0;i<32;i++) for(j=0;j<4;j++) for(k=0;k<4;k++) for(n=0;n<3;n++)
    {

/* put teapot data into single array for subdivision */

        m=indices[i][j][k];
        for(n=0;n<3;n++) data[i][j][k][n]=vertices[m-1][n];
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("teapot");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);

    glutMainLoop();

}

