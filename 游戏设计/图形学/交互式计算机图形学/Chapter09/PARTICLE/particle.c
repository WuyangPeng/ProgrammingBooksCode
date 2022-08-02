	/* sets up flat mesh */
/* sets up elapsed time parameter for use by shaders */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <GLUT/glut.h>
#include <math.h>


#define N 100

GLfloat velocity[N][2];

GLuint         program;
GLuint       vxParam, vyParam, timeParam;

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
    if (status != GL_TRUE)
    {
        printf("%s\n", msg);
        exit(EXIT_FAILURE);
    }
}

/* standard OpenGL initialization */

static void init()
{

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0,0.0,0.0);
    glPointSize(10.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1.0,0.0,1.0);

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

    timeParam = glGetUniformLocation(program, "time");
    vxParam = glGetAttribLocation(program, "vx");
    vyParam = glGetAttribLocation(program, "vy");
}

static void draw(void)
{
    int i;
    /* send elapsed time to shaders */

    glUniform1f(timeParam, glutGet(GLUT_ELAPSED_TIME));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POINTS);
       for(i=0; i<N; i++) 
       {
           glVertexAttrib1f(vxParam, velocity[i][0]);
           glVertexAttrib1f(vyParam, velocity[i][1]);
           glVertex2f(0.5, 0.5);
       }
    glEnd();

    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1.0,0.0,1.0);

    glViewport(0, 0, w, h);
}

static void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
    case 'Q':
    case 'q':
        exit(EXIT_SUCCESS);
        break;
    default:
        break;
    }
}

void idle()
{
   glutPostRedisplay();
}

int main(int argc, char** argv)
{

    int i;
    for(i=0;i<N;i++)
    {
      velocity[i][0]=2.0*((random()%256)/256.0-0.5);
      velocity[i][1]=2.0*((random()%256)/256.0-0.5);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Simple GLSL example");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    init();
    initShader("vparticle.glsl", "fPassthrough.glsl");
   

    glutMainLoop();
    return 0;
}
