
/* Robot program (Chapter 8). Cylinder for base, scaled cube for arms */
/* Shows use of instance transformation to define parts (symbols) */
/* The cylinder is a quadric object from the GLU library */
/* The cube is also obtained from GLU */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

/* Let's start using #defines so we can better
interpret the constants (and change them) */

#define BASE_HEIGHT 2.0
#define BASE_RADIUS 1.0
#define LOWER_ARM_HEIGHT 5.0
#define LOWER_ARM_WIDTH 0.5
#define UPPER_ARM_HEIGHT 5.0
#define UPPER_ARM_WIDTH 0.5

typedef float point[3];

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 0;
GLUquadricObj  *p; /* pointer to quadric object */

/* Define the three parts */
/* Note use of push/pop to return modelview matrix
to its state before functions were entered and use
rotation, translation, and scaling to create instances
of symbols (cube and cylinder */

void base()
{
   glPushMatrix();

/* rotate cylinder to align with y axis */

   glRotatef(-90.0, 1.0, 0.0, 0.0);

/* cyliner aligned with z axis, render with
   5 slices for base and 5 along length */

   gluCylinder(p, BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT, 5, 5);
   glPopMatrix();
}

void upper_arm()
{
   glPushMatrix();
   glTranslatef(0.0, 0.5*UPPER_ARM_HEIGHT, 0.0);
   glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
   glutWireCube(1.0);
   glPopMatrix();
}

void lower_arm()
{
   glPushMatrix();
   glTranslatef(0.0, 0.5*LOWER_ARM_HEIGHT, 0.0);
   glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
   glutWireCube(1.0);
   glPopMatrix();
}

void display(void)
{

/* Accumulate ModelView Matrix as we traverse tree */

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    base();
    glTranslatef(0.0, BASE_HEIGHT, 0.0);
    glRotatef(theta[1], 0.0, 0.0, 1.0);
    lower_arm();
    glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    upper_arm();
    glFlush();
    glutSwapBuffers();
}



void mouse(int btn, int state, int x, int y)
{

/* left button increase joint angle, right button decreases it */

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
        {
        theta[axis] += 5.0;
        if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
        }
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
        {
        theta[axis] -= 5.0;
        if( theta[axis] < 360.0 ) theta[axis] += 360.0;
        }
        display();
}

void menu(int id)
{

/* menu selects which angle to change or whether to quit */

   if(id == 1 ) axis=0;
   if(id == 2) axis=1;
   if(id == 3 ) axis=2;
   if(id ==4 ) exit(0);
}

void 
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -5.0 * (GLfloat) h / (GLfloat) w,
            15.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
            10.0 * (GLfloat) w / (GLfloat) h, -5.0, 15.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myinit()
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glColor3f(1.0, 0.0, 0.0);

   p=gluNewQuadric(); /* allocate quadric object */
   gluQuadricDrawStyle(p, GLU_LINE); /* render it as wireframe */
}

void
main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("robot");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("base", 1);
    glutAddMenuEntry("lower arm", 2);
    glutAddMenuEntry("upper arm", 3);
    glutAddMenuEntry("quit", 4);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
}
