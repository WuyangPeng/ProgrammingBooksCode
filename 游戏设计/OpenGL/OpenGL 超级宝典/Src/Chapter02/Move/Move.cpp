// Move.cpp
// Move a Block based on arrow key movements

#include <GLTools.h>	// OpenGL toolkit
#include <GLShaderManager.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch	squareBatch;
GLShaderManager	shaderManager;


GLfloat blockSize = 0.1f;
GLfloat vVerts[] = { -blockSize, -blockSize, 0.0f, 
	                  blockSize, -blockSize, 0.0f,
					  blockSize,  blockSize, 0.0f,
					 -blockSize,  blockSize, 0.0f};

///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context. 
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
    
	shaderManager.InitializeStockShaders();

	// Load up a triangle
	squareBatch.Begin(GL_TRIANGLE_FAN, 4);
	squareBatch.CopyVertexData3f(vVerts);
	squareBatch.End();
	}

// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
    {
	GLfloat stepSize = 0.025f;

	GLfloat blockX = vVerts[0];   // Upper left X
	GLfloat blockY = vVerts[7];  // Upper left Y

	if(key == GLUT_KEY_UP)
		blockY += stepSize;

	if(key == GLUT_KEY_DOWN)
		blockY -= stepSize;
	
	if(key == GLUT_KEY_LEFT)
		blockX -= stepSize;

	if(key == GLUT_KEY_RIGHT)
		blockX += stepSize;

	// Collision detection
	if(blockX < -1.0f) blockX = -1.0f;
	if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2;;
	if(blockY < -1.0f + blockSize * 2)  blockY = -1.0f + blockSize * 2;
	if(blockY > 1.0f) blockY = 1.0f;

	// Recalculate vertex positions
	vVerts[0] = blockX;
	vVerts[1] = blockY - blockSize*2;
	
	vVerts[3] = blockX + blockSize*2;
	vVerts[4] = blockY - blockSize*2;
	
	vVerts[6] = blockX + blockSize*2;
	vVerts[7] = blockY;

	vVerts[9] = blockX;
	vVerts[10] = blockY;

	squareBatch.CopyVertexData3f(vVerts);

	glutPostRedisplay();
	}





///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
	{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	squareBatch.Draw();

	// Flush drawing commands
	glutSwapBuffers();
	}



///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
	{
	glViewport(0, 0, w, h);
	}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
	{
	gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Move Block with Arrow Keys");
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
		{
		// Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 1;
		}
	
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);

	SetupRC();

	glutMainLoop();
	return 0;
	}
