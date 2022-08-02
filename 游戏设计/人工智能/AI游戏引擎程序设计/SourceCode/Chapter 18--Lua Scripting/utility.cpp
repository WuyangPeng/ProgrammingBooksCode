#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include <GL/glut.h>
#include "utility.h"

Point3f colorArray[16];

//---------------------------------------------------------
void glInitColorArray()
{
	//white
	colorArray[0] = Point3f(1,1,1);
	//red
	colorArray[1] = Point3f(1,0,0);
	//green
	colorArray[2] = Point3f(0,1,0);
	//blue
	colorArray[3] = Point3f(0,0,1);
	//black
	colorArray[4] = Point3f(0,0,0);
	//gray
	colorArray[5] = Point3f(0.5f,0.5f,0.5f);
	//cyan
	colorArray[6] = Point3f(0,1,1);
	//yellow
	colorArray[7] = Point3f(1,1,0);
	//magenta
	colorArray[8] = Point3f(1,0,1);
    //silver
    colorArray[9] = Point3f(0.75f,0.75f,0.75f);
    //maroon
    colorArray[10]= Point3f(0.5f,0,0);
    //dk green
    colorArray[11]= Point3f(0,0.5f,0);
    //dk blue
    colorArray[12]= Point3f(0,0,0.5f);
    //purple
    colorArray[13]= Point3f(0.5f,0,0.5f);
    //olive
    colorArray[14]= Point3f(0.5f,0.5f,0);
    //teal
    colorArray[15]= Point3f(0,0.5f,0.5f);
    
}

//---------------------------------------------------------
void glPrintf(int color, GLuint x, GLuint y, GLfloat scale, char* format, ...)
{
    va_list args;
    char buffer[255], *p;
    GLfloat font_scale = 119.05f + 33.33f;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
	
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glTranslatef(x, y, 0.0);
	glColor3f(colorArray[color].x(),colorArray[color].y(),colorArray[color].z());
	
    glScalef(scale/font_scale, scale/font_scale, scale/font_scale);
	
    for(p = buffer; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	
    glPopAttrib();
	
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

//---------------------------------------------------------
float FPS(int lastFrameTime)
{
	static int LastTimes[10]={0,0,0,0,0,0,0,0,0,0};
	static int c=0;
	int i;
	float average=0;
	c=(c+1)%10;
	LastTimes[c]=lastFrameTime;
	
	for(i=0;i<10;i++)
		average+=LastTimes[i];
	return 1000.0/(average/10.0);
}

