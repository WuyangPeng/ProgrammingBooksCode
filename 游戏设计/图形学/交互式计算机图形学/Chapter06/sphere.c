
/* Recursive subdivision of cube (Chapter 6). Three display
modes: wire frame, constant, and interpolative shading */

/*Program also illustrates defining materials and light sources
in myiit() */

/* mode 0 = wire frame, mode 1 = constant shading,
mode 3 = interpolative shading */

#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


typedef float point[4];

/* initial tetrahedron */

point v[]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},
          {-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};

int n;
int mode;


void triangle( point a, point b, point c)

/* display one triangle using a line loop for wire frame, a single
normal for constant shading, or three normals for interpolative shading */
{
    if (mode==0) glBegin(GL_LINE_LOOP);
    else glBegin(GL_POLYGON);
       if(mode==1) glNormal3fv(a);
       if(mode==2) glNormal3fv(a);
       glVertex3fv(a);
       if(mode==2) glNormal3fv(b);
       glVertex3fv(b);
       if(mode==2) glNormal3fv(c);
       glVertex3fv(c);
    glEnd();
}

void normal(point p)
{

/* normalize a vector */

    double sqrt();
    float d =0.0;
    int i;
    for(i=0; i<3; i++) d+=p[i]*p[i];
    d=sqrt(d);
    if(d>0.0) for(i=0; i<3; i++) p[i]/=d;
}

void divide_triangle(point a, point b, point c, int m)
{

/* triangle subdivision using vertex numbers
righthand rule applied to create outward pointing faces */

    point v1, v2, v3;
    int j;
    if(m>0)
    {
        for(j=0; j<3; j++) v1[j]=a[j]+b[j];
        normal(v1);
        for(j=0; j<3; j++) v2[j]=a[j]+c[j];
        normal(v2);
        for(j=0; j<3; j++) v3[j]=b[j]+c[j];
         normal(v3);
        divide_triangle(a, v1, v2, m-1);
        divide_triangle(c, v2, v3, m-1);
        divide_triangle(b, v3, v1, m-1);
        divide_triangle(v1, v3, v2, m-1);
    }
    else(triangle(a,b,c)); /* draw triangle at end of recursion */
}

void tetrahedron( int m)
{

/* Apply triangle subdivision to faces of tetrahedron */

    divide_triangle(v[0], v[1], v[2], m);
    divide_triangle(v[3], v[2], v[1], m);
    divide_triangle(v[0], v[3], v[1], m);
    divide_triangle(v[0], v[2], v[3], m);
}

void display(void)
{

/* Displays all three modes, side by side */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   glLoadIdentity();
    mode=0;
    tetrahedron(n);
    mode=1;
    glTranslatef(-2.0, 0.0,0.0);
    tetrahedron(n);
    mode=2;
    glTranslatef( 4.0, 0.0,0.0);
    tetrahedron(n);


    glFlush();
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
            4.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    display();
}


void myinit()
{
    GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess={100.0};
    GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};

/* set up ambient, diffuse, and specular components for light 0 */

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

/* define material proerties for front face of all polygons */

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH); /*enable smooth shading */
    glEnable(GL_LIGHTING); /* enable lighting */
    glEnable(GL_LIGHT0);  /* enable light 0 */
    glEnable(GL_DEPTH_TEST); /* enable z buffer */

    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f (0.0, 0.0, 0.0);
}


void
main(int argc, char **argv)
{
    n=5;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("sphere");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMainLoop();
}
