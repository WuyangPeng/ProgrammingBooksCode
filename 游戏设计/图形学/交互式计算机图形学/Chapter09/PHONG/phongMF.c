/* display teapot with vertex and fragment shaders */
/* sets up elapsed time parameter for use by shaders */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <GLUT/glut.h>


const GLdouble nearVal     = 1.0;
const GLdouble farVal      = 20.0;
const GLfloat  lightPos[4] = {3.0f, 3.0f, 3.0f, 1.0f};
GLuint         program     = 0;
GLint          timeParam;

/* shader reader */
/* creates null terminated string from file */

static char* readShaderSource(const char* shaderFile)
{
    struct stat statBuf;
    FILE* fp = fopen(shaderFile, "r");
    char* buf;

    stat(shaderFile, &statBuf);
    buf = (char*) malloc((statBuf.st_size + 1) * sizeof(char));
    fread(buf, 1, statBuf.st_size, fp);
    buf[statBuf.st_size] = '\0';
    fclose(fp);
    return buf;
}

/* error printing function */

static void checkError(GLint status, const char *msg)
{
    if (!status)
    {
        printf("%s\n", msg);
        exit(EXIT_FAILURE);
    }
}

/* standard OpenGL initialization */

static void init()
{
    const float teapotColor[]     = {0.3f, 0.5f, 0.4f, 1.0f}; 
    const float teapotSpecular[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    const float teapotShininess[] = {80.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, teapotColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShininess);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double) glutGet(GLUT_WINDOW_WIDTH) / (double) glutGet(GLUT_WINDOW_HEIGHT), nearVal, farVal);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

/* GLSL initialization */

static void initShader(const GLchar* vShaderFile, const GLchar* fShaderFile)
{
    GLint status = glGetError()==GL_NO_ERROR; 
    GLchar *vSource, *fSource;
    GLuint vShader, fShader;

    /* read shader files */

    vSource = readShaderSource(vShaderFile);
    checkError(status, "Failed to read vertex shader");

    fSource = readShaderSource(fShaderFile);
    checkError(status, "Failed to read fragment shader");

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
    glGetShaderiv(program, GL_LINK_STATUS, &status);
    checkError(status, "Failed to link the shader program object.");

    /* use program object */

    glUseProgram(program);

    /* set up uniform parameter */

    timeParam = glGetUniformLocation(program, "time");
}

static void draw(void)
{
    /* send elapsed time to shaders */

    glUniform1f(timeParam, glutGet(GLUT_ELAPSED_TIME));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double) w / (double) h, nearVal, farVal);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    default:
        break;
    }
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

    init();
    initShader("vFragPhong.glsl", "fPhong.glsl");

    glutMainLoop();
    return 0;
}
