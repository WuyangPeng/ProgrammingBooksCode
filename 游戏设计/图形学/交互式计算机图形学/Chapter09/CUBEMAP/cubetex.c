
#include <stdlib.h>
#include <GLUT/glut.h>


static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

    GLuint tex;

void display(void)
{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glutSolidTeapot(1.0);


	glutSwapBuffers();
}

void spinCube()
{


	theta[axis] += 2.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void key(char k, int x, int y)
{
	if(k == '1') glutIdleFunc(spinCube);
	if(k == '2') glutIdleFunc(NULL);
        if(k == 'q') exit(0);
}

void init()
{

    GLubyte red[3] = {255, 0, 0};
    GLubyte green[3] = {0, 255, 0};
    GLubyte blue[3] = {0, 0, 255};
    GLubyte cyan[3] = {0, 255, 255};
    GLubyte magenta[3] = {255, 0, 255};
    GLubyte yellow[3] = {255, 255, 0};

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);
    glEnable(GL_TEXTURE_CUBE_MAP);

   glGenTextures(1, &tex);
   glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);
   glTexGeni(GL_R, GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, red);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, green);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, blue);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, cyan);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, magenta);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ,0,3,1,1,0,GL_RGB,GL_UNSIGNED_BYTE, yellow);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_REPEAT);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_REPEAT);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 

   glClearColor(1.0,1.0,1.0,1.0);
}

void
main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("colorcube");

    init();

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutIdleFunc(NULL);
    glutMouseFunc(mouse);

    glutKeyboardFunc(key);
    glutMainLoop();
}
