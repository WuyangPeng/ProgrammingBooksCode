	/* sets up flat mesh */
/* sets up elapsed time parameter for use by shaders */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <GLUT/glut.h>
#include <math.h>

#define N 256
#define a 0.1
#define b 50.0

GLfloat normals[N][N][3];
const GLdouble nearVal     = 1.0;
const GLdouble farVal      = 20.0;
GLfloat  lightPos[4] = {0.0, 10.0, 0.0, 1.0};
GLuint         program     = 0;
/* GLint          timeParam; */
GLuint        texHandle;
GLuint        texMapLocation;
GLint          tangentParam;
const GLfloat tangent[3] = {1.0, 0.0, 0.0};

/* shader reader */
/* creates null terminated string from file */

static char* readShaderSource(const char* shaderFile)
{
    struct stat statBuf;
    FILE* fp = fopen(shaderFile, "r");
    char* buf;

    stat(shaderFile, &statBuf);
    if(fp==NULL) return NULL;
    buf = (char*) malloc((statBuf.st_size + 1) * sizeof(char));
    fread(buf, 1, statBuf.st_size, fp);
    buf[statBuf.st_size] = '\0';
    fclose(fp);
    return buf;
}

/* error printing function */

static void checkError(GLint status, const char *msg)
{
    if (status == GL_FALSE)
    {
        printf("%s\n", msg);
        exit(EXIT_FAILURE);
    }
}

/* standard OpenGL initialization */

static void init()
{
    const float meshColor[]     = {0.7f, 0.7f, 0.7f, 1.0f}; 
    const float meshSpecular[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    const float meshShininess[] = {80.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, meshColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, meshSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, meshShininess);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glGenTextures(1, &texHandle);
    glBindTexture(GL_TEXTURE_2D, texHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, N, N, 0, GL_RGB, GL_FLOAT, normals);
     glEnable(GL_TEXTURE_2D);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.75,0.75,-0.75,0.75,-5.5,5.5);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
     glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

/* GLSL initialization */

static void initShader(const GLchar* vShaderFile, const GLchar* fShaderFile)
{
    GLint status; 
    GLchar *vSource, *fSource;
    GLuint vShader, fShader;

    /* read shader files */

    vSource = readShaderSource(vShaderFile);
    if(vSource==NULL)
    {
        printf( "Failed to read vertex shaderi\n");
        exit(EXIT_FAILURE);
    }

    fSource = readShaderSource(fShaderFile);
    if(fSource==NULL)
    {
        printf("Failed to read fragment shader");
        exit(EXIT_FAILURE);
    }

    /* create program and shader objects */

    vShader = glCreateShader(GL_VERTEX_SHADER);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    program = glCreateProgram();

    /* attach shaders to the program object */

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    /* read shaders */

    glShaderSource(vShader, 1, (const GLchar**) &vSource, NULL);
    glShaderSource(fShader, 1, (const GLchar**) &fSource, NULL);

    /* compile shaders */

    glCompileShader(vShader);
    glCompileShader(fShader);

    /* error check */

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);
    checkError(status, "Failed to compile the vertex shader.");

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &status);
    checkError(status, "Failed to compile the fragment shader.");

    /* link */

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    checkError(status, "Failed to link the shader program object.");

    /* use program object */

    glUseProgram(program);

    /* set up uniform parameter */

    tangentParam = glGetAttribLocation(program, "objTangent");
    /* timeParam = glGetUniformLocation(program, "time"); */
    texMapLocation = glGetUniformLocation(program, "texMap");
}

void mesh()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.5, 0.0, 0.5, 0.0, 1.0, 0.0);
       glNormal3f(0.0,1.0,0.0);
       glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0);
       glVertex3f(0.0, 0.0, 0.0);
       glTexCoord2f(1.0, 0.0);
       glVertex3f(1.0, 0.0, 0.0);
       glTexCoord2f(1.0, 1.0);
       glVertex3f(1.0,0.0,1.0);
       glTexCoord2f(0.0, 1.0);
       glVertex3f(0.0,0.0,1.0);
       glEnd();
}

static void draw(void)
{

    /* glUniform1f(timeParam, glutGet(GLUT_ELAPSED_TIME)); */

    glVertexAttrib3fv(tangentParam, tangent);
    glUniform1i(texMapLocation, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     mesh(); 
    /* glutSolidTeapot(0.4); */
    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.75,0.75,-0.75,0.75,-5.5,5.5);

    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
    case 'Q':
    case 'q':
        exit(EXIT_SUCCESS);
        break;
    case '1':
         lightPos[0] = 10.0;
         lightPos[1] = 10.0;
         lightPos[2] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
         glutPostRedisplay();
         break;
    case '2':
         lightPos[0] = 7.0;
         lightPos[1] = 10.0;
         lightPos[2] = 7.0;
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
         glutPostRedisplay();
         break;
    default:
        break;
    }
}

void idle()
{
   int t;
   /* glUniform1f(timeParam, glutGet(GLUT_ELAPSED_TIME)); */
   t = glutGet(GLUT_ELAPSED_TIME);
   lightPos[0] = 5.5*sin(0.001*t);
   lightPos[2] = 5.5*cos(0.001*t);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
    int i,j,k;
    float d;
    
    float data[N+1][N+1];
    for(i=0;i<N+1;i++) for(j=0;j<N+1;j++) data[i][j]=0.0;
    for(i=N/4; i< 3*N/4; i++) for(j=N/4;j<3*N/4;j++) data[i][j] = 100.5;

    for(i=0;i<N;i++) for(j=0;j<N;j++) 
    {
       normals[i][j][0] = a*b+sin(b*i/(float)N)*(float)cos(b*j/(float)N);
       normals[i][j][1] = a*b+sin(b*j/(float)N)*cos(b*i/(float)N);
       normals[i][j][2]=1.0;
    }
    for(i=0;i<N;i++) for(j=0;j<N;j++)
    {
       normals[i][j][0] = data[i][j]-data[i+1][j];
       normals[i][j][1] = data[i][j]-data[i][j+1];
       normals[i][j][2]=1.0;
    }
    for(i=0;i<N;i++) for(j=0;j<N;j++) 
    {
       d = 0.0;
       for(k=0;k<3;k++) d+=normals[i][j][k]*normals[i][j][k];
       d=sqrt(d);
       for(k=0;k<3;k++) normals[i][j][k]= 0.5*normals[i][j][k]/d+0.5;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("Simple GLSL example");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    init();
    initShader("vBump.glsl", "fBump3.glsl");
   

    glutMainLoop();
    return 0;
}
