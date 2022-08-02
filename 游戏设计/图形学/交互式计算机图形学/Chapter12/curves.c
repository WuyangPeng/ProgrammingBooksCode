/*
**  curves.c
**
**  Simple curve drawing program.
**
**  The following keyboard commands are used to control the
**  program:
**
**    q - Quit the program
**    c - Clear the screen
**    e - Erase the curves
**    b - Draw Bezier curves
**    i - Draw interpolating curves
**    s - Draw B-spline curves
**
*/


#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef enum
{
    BEZIER,
    INTERPOLATED,
    BSPLINE
} curveType;

void keyboard(unsigned char key, int x, int y);
void computeMatrix(curveType type, float m[4][4]);
void vmult(float m[4][4], float v[4][3], float r[4][3]);

/* Colors to draw them in */
GLfloat colors[][3] =
{
   { 1.0, 0.0, 0.0 },
   { 0.0, 1.0, 0.0 },
   { 0.0, 0.0, 1.0 }
};


#define MAX_CPTS  25            /* Fixed maximum number of control points */

GLfloat cpts[MAX_CPTS][3];
int ncpts = 0;

static int width = 500, height = 500;           /* Window width and height */


/* Matrix stuff */

/* This routine multiplies two 4 x 4 matrices. */

/* This routine multiplies a 4 x 4 matrix with a vector of 4 points. */
void vmult(float m[4][4], float v[4][3], float r[4][3])
{
    int i, j, k;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            for (k = 0, r[i][j] = 0.0; k < 4; k++)
                r[i][j] += m[i][k] * v[k][j];
}


/* Interpolating to Bezier matrix */
static float minterp[4][4] = 
{
    { 1.0, 0.0, 0.0, 0.0 },
    { -5.0/6.0, 3.0, -3.0/2.0, 1.0/3.0 },
    { 1.0/3.0, -3.0/2.0, 3.0, -5.0/6.0 },
    { 0.0, 0.0, 0.0, 1.0 }, 
};

/* B-spline to Bezier matrix */
static float mbspline[4][4] = 
{
    { 1.0/6.0, 4.0/6.0, 1.0/6.0, 0.0 },
    { 0.0, 4.0/6.0, 2.0/6.0, 0.0 },
    { 0.0, 2.0/6.0, 4.0/6.0, 0.0 },
    { 0.0, 1.0/6.0, 4.0/6.0, 1.0/6.0 },
};

static float midentity[4][4] =
{
	{ 1.0, 0.0, 0.0, 0.0},
	{ 0.0, 1.0, 0.0, 0.0},
	{ 0.0, 0.0, 1.0, 0.0},
	{ 0.0, 0.0, 0.0, 1.0}
};



/* Calculate the matrix used to transform the control points */
void computeMatrix(curveType type, float m[4][4])
{
    int i, j;

    switch (type)
    {
        case BEZIER:
            /* Identity matrix */
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
					m[i][j] = midentity[i][j];
            break;
        case INTERPOLATED:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    m[i][j] = minterp[i][j];
            break;
        case BSPLINE:
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    m[i][j] = mbspline[i][j];
            break;
     }
}

/* Draw the indicated curves using the current control points. */
static void drawCurves(curveType type)
{
    int i;
    int step;
    GLfloat newcpts[4][3];

    float m[4][4];

    /* Set the control point computation matrix and the step size. */
    computeMatrix(type, m);

	if(type == BSPLINE) step = 1;
	else step = 3;

    glColor3fv(colors[type]);

    /* Draw the curves */
    i = 0;
    while (i + 3 < ncpts)
    {
        /* Calculate the appropriate control points */
        vmult(m, &cpts[i], newcpts);

        /* Draw the curve using OpenGL evaluators */
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &newcpts[0][0]);
        glMapGrid1f(30, 0.0, 1.0);
        glEvalMesh1(GL_LINE, 0, 30);

        /* Advance to the next segment */
        i += step;
    }
    glFlush();
}

/* This routine displays the control points */
static void display(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (i = 0; i < ncpts; i++)
        glVertex3fv(cpts[i]);
    glEnd();

    glFlush();
}


/* This routine inputs new control points */
static void mouse(int button, int state, int x, int y)
{
    float wx, wy;

    /* We are only interested in left clicks */
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    /* Translate back to our coordinate system */
    wx = (2.0 * x) / (float)(width - 1) - 1.0;
    wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;


    /* See if we have room for any more control points */
    if (ncpts == MAX_CPTS)
        return;

    /* Save the point */
    cpts[ncpts][0] = wx;
    cpts[ncpts][1] = wy;
    cpts[ncpts][2] = 0.0;
    ncpts++;

    /* Draw the point */
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(wx, wy, 0.0);
    glEnd();
 
    glFlush();
}


/* This routine handles keystroke commands */
void keyboard(unsigned char key, int x, int y)
{
    static curveType lasttype = BEZIER;

    switch (key)
    {
        case 'q': case 'Q':
            exit(0);
            break;
        case 'c': case 'C':
			ncpts = 0;
			glutPostRedisplay();
            break;
        case 'e': case 'E':
            glutPostRedisplay();
            break;
        case 'b': case 'B':
            drawCurves(BEZIER);
            lasttype = BEZIER; 
            break;
        case 'i': case 'I':
            drawCurves(INTERPOLATED);
            lasttype = INTERPOLATED; 
            break;
        case 's': case 'S':
            drawCurves(BSPLINE);
            lasttype = BSPLINE; 
            break;
    }
}


/* This routine handles window resizes */
void reshape(int w, int h)
{
    width = w;
    height = h;

    /* Set the transformations */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}


main(int argc, char **argv)
{
    /* Intialize the program */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("curves");

    /* Register the callbacks */
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_MAP1_VERTEX_3);


    glutMainLoop();
}
