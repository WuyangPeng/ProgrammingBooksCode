	/* sets up flat mesh */
/* sets up elapsed time parameter for use by shaders */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <GLUT/glut.h>

GLuint         program;
GLint          timeParam;
GLint          vertices_two_location;

const GLfloat vertices_one[3][2] = {{0.0, 0.0},{0.5,1.0},{1.0, 0.0}};
const GLfloat vertices_two[3][2] = {{0.0, 1.0},{0.5,0.0},{1.0, 1.0}};

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
    vertices_two_location = glGetAttribLocation(program, "vertices2");
}

static void draw(void)
{
    /* send elapsed time to shaders */

    glUniform1f(timeParam, glutGet(GLUT_ELAPSED_TIME));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
       glVertexAttrib2fv(vertices_two_location, &vertices_two[0][0]); 
       glVertex2fv(vertices_one[0]);
       glVertexAttrib2fv(vertices_two_location, &vertices_two[1][0]); 
       glVertex2fv(vertices_one[1]);
       glVertexAttrib2fv(vertices_two_location, &vertices_two[2][0]); 
       glVertex2fv(vertices_one[2]);
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
   glUniform1f(timeParam, glutGet(GLUT_ELAPSED_TIME));
   glutPostRedisplay();
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Simple GLSL example");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    init();
    initShader("vmorph.glsl", "fPassthrough.glsl");
   

    glutMainLoop();
    return 0;
}
