/* sets up flat mesh */
/* sets up elapsed time parameter for use by shaders */
/* uses a modified phong vertex shader and a pass through fragment shader */
/* vertex shader varies height of mesh sinusoidally */

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#define N 64

const GLdouble nearVal     = 1.0; /* near distance */
const GLdouble farVal      = 20.0; /* far distance */
const GLfloat  lightPos[4] = {0.0f, 3.0f, -3.0f, 1.0f}; /* light position */
GLuint         program     = 0; /* program object id */
GLint          timeParam;

GLchar *ebuffer; /* buffer for error messages */
GLsizei elength; /* length of error message */

GLfloat data[N][N]; /* array of data heights */

/* shader reader */
/* creates null terminated string from file */

static char* readShaderSource(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "r");
    char* buf;
    long size;

    if(fp==NULL) return NULL;
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    buf = (char*) malloc((size + 1) * sizeof(char)); 
    fread(buf, 1, size, fp);
    fclose(fp);
    return buf;
}

/* standard OpenGL initialization */

static void init()
{
    const float meshColor[]     = {0.3f, 0.5f, 0.4f, 1.0f}; 
    const float meshSpecular[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    const float meshShininess[] = {80.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, meshColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, meshSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, meshShininess);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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

    /* compile vertex shader shader */

    glCompileShader(vShader);

    /* error check */

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);
    if(status==GL_FALSE)
    {
       printf("Failed to compile the vertex shader.\n");
       glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &elength);
       ebuffer = malloc(elength*sizeof(char));
       glGetShaderInfoLog(vShader, elength, NULL, ebuffer);
       printf("%s\n", ebuffer);
       exit(EXIT_FAILURE);
    }

    /* compile fragment  shader shader */

    glCompileShader(fShader);

    /* error check */

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &status);
    if(status==GL_FALSE)
    {
       printf("Failed to compile the fragment shader.\n");
       glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &elength);
       ebuffer = malloc(elength*sizeof(char));
       glGetShaderInfoLog(fShader, elength, NULL, ebuffer);
       printf("%s\n", ebuffer); 
       exit(EXIT_FAILURE);
    }

    /* link  and error check */

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status==GL_FALSE)
    {
       printf("Failed to link program object.\n");
       glGetProgramiv(program, GL_INFO_LOG_LENGTH, &elength);
       ebuffer = malloc(elength*sizeof(char));
       glGetProgramInfoLog(program, elength, &elength, ebuffer);
       printf("%s\n", ebuffer);
       exit(EXIT_FAILURE);
    }

    /* use program object */

    glUseProgram(program);

    /* set up uniform parameter */

    timeParam = glGetUniformLocation(program, "time");
}

void mesh()
{
    int i,j;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.5, 0.0, 0.5, 0.0, 1.0, 0.0);
    glNormal3f(0.0,1.0,0.0); 
    glBegin(GL_QUADS);
    for(i=0; i<N; i++) for(j=0; j<N;j++)
    {
       glVertex3f((float)i/N, data[i][j], (float)j/N);
       glVertex3f((float)i/N, data[i][j], (float)(j+1)/N);
       glVertex3f((float)(i+1)/N, data[i][j], (float)(j+1)/N);
       glVertex3f((float)(i+1)/N, data[i][j], (float)(j)/N);
    }
    glEnd();
}

static void draw(void)
{
    /* send elapsed time to shaders */

    glUniform1f(timeParam, glutGet(GLUT_ELAPSED_TIME));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mesh();
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
    int i,j;

    for(i=0;i<N;i++) for(j=0;j<N;j++) data[i][j]=0.0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Simple GLSL example");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    init();
    initShader("vwave.glsl", "fPassthrough.glsl");

    glutMainLoop();
    return 0;
}
