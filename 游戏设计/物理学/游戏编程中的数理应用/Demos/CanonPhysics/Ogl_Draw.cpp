#include "Ogl_Draw.h"

#include <gl\gl.h>
#include <gl\glu.h>

#include <cstdio>
#include <cstdarg>

//	Default Constructor.
Ogl_Draw::Ogl_Draw()
{
	fontdisplaylist = 0;
}

Ogl_Draw::~Ogl_Draw()
{
	glDeleteLists(fontdisplaylist, 256);	//	Delete the 2D font display list.
	glDeleteLists(outlinefontdlist, 256);	//	Delete the 3D font display list.
}

//	ChooseFont : Choose the Font to use when printing strings to the Screen.
//
//	Input	:	*fontname	-	The Font to use.  Default is Courier New.
//				fontheight	-	How big do you want the font to be.
//
//	Return	:	True if Successful.
bool Ogl_Draw::ChooseFont(HDC hDC, int fontheight, char *fontname)
{
	char buffer[256] = {0};			//	For Error Messages.
	//	Make sure fontdisplay hasn't already been initialized.
	//	If it is then Delete the list before generating more.
	if (fontdisplaylist)
	{
		glDeleteLists(fontdisplaylist, 256);
		fontdisplaylist = 0;
	}
	//	Make sure outlinefontdlist was initialized.
	if (outlinefontdlist)
	{
		glDeleteLists(outlinefontdlist, 256);
		outlinefontdlist = 0;
	}

	HFONT font = NULL;						//	Windows Font ID.
	fontdisplaylist = glGenLists(256);		//	Hold the Display List for 2D fonts.
	outlinefontdlist = glGenLists(256);		//	Hold the Display List for 3D fonts.

	//	Create the Font.
	font = CreateFont(	fontheight * -1,				//	Height Of Font
						0,								//	Width Of Font
						0,								//	Angle Of Escapement
						0,								//	Orientation Angle
						FW_BOLD,						//	Font Weight
						FALSE,							//	Italic
						FALSE,							//	Underline
						FALSE,							//	Strikeout
						ANSI_CHARSET,					//	Character Set Identifier
						OUT_TT_PRECIS,					//	Output Precision
						CLIP_DEFAULT_PRECIS,			//	Clipping Precision
						ANTIALIASED_QUALITY,			//	Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		//	Family And Pitch
						fontname);						//	Font Name
	//	Make sure the font was created.
	if (!font)
	{
		sprintf(buffer, "Could not create font %s", fontname);
		MessageBox(NULL, buffer, "Ogl_Draw Error", MB_OK);
		return false;
	}

	//	Select the Font to use.
	SelectObject(hDC, font);

	//	Build the 2D and 3D font display lists.
	wglUseFontBitmaps(hDC, 0, 255, fontdisplaylist);
	wglUseFontOutlines(hDC, 0, 255,	outlinefontdlist, 0.0f,	0.2f, WGL_FONT_POLYGONS, glyph);

	DeleteObject(font);

	//	Return Success.
	return true;
}

//	TextOut : Simplest form of the TextOut function.  You just pass in the string to print to the
//			  screen.  You have to specify the color and position with calls to glColor3ub() and
//			  glRasterPos3f().	This function can be used much like sprintf.
//
//	Input	:	*string		-	The String to print out.
//				...			-	The Variable Argument list.  This is for functionality like sprintf();
//
//	Return	:	True if Successful.
bool Ogl_Draw::TextOut(const char *string, ...)
{
	//	Make sure fontdisplaylist and string are valid.
	if (!fontdisplaylist || !string)
		return false;

	char buffer[512] = {0};									//	Holds Our String.
	float length = 0;										//	The physical lenght of the String.
	va_list	ap;												//	Pointer To List Of Arguments.

	va_start(ap, string);									//	Parses The String For Variables
	    vsprintf(buffer, string, ap);						//	And Converts Symbols To Actual Numbers
	va_end(ap);												//	Results Are Stored In buffer

	glPushAttrib(GL_LIST_BIT);								//	Pushes The Display List Bits
	glListBase(fontdisplaylist);							//	Sets The Base Character to 32
	glCallLists(strlen(buffer), GL_UNSIGNED_BYTE, buffer);	//	Draws The Display List Text
	glPopAttrib();											//	Pops The Display List Bits

	//	Return Success.
	return true;
}

//	TextOut : Prints the string at the specified position and using the specified color.  This uses
//			  arrays for the positioning and coloring.
//
//	Input	:	pos[]	-	The Position Array.
//				color[]	-	The Color Array.
//				*string	-	The String to print out.
//				...		-	The Variable Argument list.
//
//	Return	:	True if Successful.
bool Ogl_Draw::TextOut(float pos[3], int color[3], const char *string, ...)
{
	//	Make sure fontdisplaylist and string are valid.
	if (!fontdisplaylist || !string)
		return false;

	char buffer[512] = {0};									//	Holds Our String.
	va_list	ap;												//	Pointer To List Of Arguments.

	va_start(ap, string);									//	Parses The String For Variables
	    vsprintf(buffer, string, ap);						//	And Converts Symbols To Actual Numbers
	va_end(ap);												//	Results Are Stored In buffer

	glColor3ub(color[0], color[1], color[2]);				//	Set the Color to use.
	glRasterPos3f(pos[0], pos[1], pos[2]);					//	Set the Position to place the String at.
	glPushAttrib(GL_LIST_BIT);								//	Pushes The Display List Bits
	glListBase(fontdisplaylist);							//	Sets The Base Character to 32
	glCallLists(strlen(buffer), GL_UNSIGNED_BYTE, buffer);	//	Draws The Display List Text
	glPopAttrib();											//	Pops The Display List Bits

	//	Return Success.
	return true;
}

//	TextOut : Prints the string at the specified position and using the specified color.  This uses
//			  individual arguments for all positions and r,g,b components.
//
//	Input	:	x		-	The X-Coordinate of where to place the String.
//				y		-	The Y-Cooridnate of where to place the String.
//				z		-	The Z-Cooridante of where to place the String.
//				r		-	The Red Component Color.
//				g		-	The Green Component Color.
//				b		-	The Blue Component Color.
//				*string	-	The String to print out.
//				...		-	The Variable Argument list.
//
//	Return	:	True if Successful.
bool Ogl_Draw::TextOut(float x, float y, float z, int r, int g, int b, const char *string, ...)
{
	//	Make sure fontdisplaylist and string are valid.
	if (!fontdisplaylist || !string)
		return false;

	char buffer[256] = {0};									//	Holds Our String.
	va_list	ap;												//	Pointer To List Of Arguments.

	va_start(ap, string);									//	Parses The String For Variables
	    vsprintf(buffer, string, ap);						//	And Converts Symbols To Actual Numbers
	va_end(ap);												//	Results Are Stored In buffer

	glColor3ub(r, g, b);									//	Set the Color to use.
	glRasterPos3f(x, y, z);									//	Set the Position to place the String at.
	glPushAttrib(GL_LIST_BIT);								//	Pushes The Display List Bits
	glListBase(fontdisplaylist);							//	Sets The Base Character to 32
	glCallLists(strlen(buffer), GL_UNSIGNED_BYTE, buffer);	//	Draws The Display List Text
	glPopAttrib();											//	Pops The Display List Bits

	//	Return Success.
	return true;
}

//	TextOut : Prints the string at the specified position using glOrtho2D.
//
//	Input	:	x		-	The X-Coordinate of where to place the String.
//				y		-	The Y-Coordinate of where to place the String.
//				*string	-	The String to print out.
//				...		-	The Variable Argument list.
//
//	Return	:	True if Successful.
bool Ogl_Draw::TextOut(float x, float y, const char *string, ...)
{
	//	Make sure fontdisplaylist and string are valid.
	if (!fontdisplaylist || !string)
		return false;

	char buffer[256] = {0};									//	Holds Our String.
	va_list	ap;												//	Pointer To List Of Arguments.

	va_start(ap, string);									//	Parses The String For Variables
	    vsprintf(buffer, string, ap);						//	And Converts Symbols To Actual Numbers
	va_end(ap);												//	Results Are Stored In buffer

	//	Set coordinate System.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 480, 0);

	//	Drawing mode.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2f(x,  y);
	glPushAttrib(GL_LIST_BIT);								//	Pushes The Display List Bits
	glListBase(fontdisplaylist);							//	Sets The Base Character to 32
	glCallLists(strlen(buffer), GL_UNSIGNED_BYTE, buffer);	//	Draws The Display List Text
	glPopAttrib();											//	Pops The Display List Bits

	//	Setup the aspect Ratio for Persepective Frustrum,
	float aspect = float(GetSystemMetrics(SM_CXSCREEN)) / float(GetSystemMetrics(SM_CYSCREEN));

	//	Set coordinate System.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	Can't use 0 for Near Clipping Plane.  This sets up our Perspective Frustrum for OpenGL.
	gluPerspective(90.0f, aspect, 0.01f, 1000.0f);

	//	Drawing mode.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//	Return Success.
	return true;
}

//	TextOut3D : Output a String in 3D.  The Color can be set with glColor3ub and you can
//				move it about with glTranslatef() and such.
//
//	Input	:	*string	-	The String to print out.
//				...		-	The Variable Argument list.
//
//	Return	:	True if Successful.
bool Ogl_Draw::TextOut3D(const char *string, ...)
{
	//	Make sure diplay list and string are valid.
	if (!outlinefontdlist || !string)
		return false;

	char buffer[512] = {0};									//	Used to hold the string.
	float length = 0;										//	Physical length of the string.
	va_list ap;												//	Pointer to the list of Arguments.

	va_start(ap, string);									//	Parses the string for variables.
		vsprintf(buffer, string, ap);						//	Converts symbols to actual numbers.
	va_end(ap);												//	Results are stored int buffer.

	//	Loop to find text length.
	for (unsigned int loop = 0;loop < (strlen(buffer)); loop++)
	{
		//	Increase Length By Each Characters Width.
		length+=glyph[buffer[loop]].gmfCellIncX;
	}

	glPushAttrib(GL_LIST_BIT);								//	Pushes the display list bits.
	glListBase(outlinefontdlist);							//	Sets the base display list to use.
	glCallLists(strlen(buffer), GL_UNSIGNED_BYTE, buffer);	//	Draws the display list text.
	glPopAttrib();											//	Pops the display list bits.
	
	//	Return Success.
	return true;
}

//	TextOut : Prints the string at the specified position using glOrtho2D.
//
//	Input	:	x		-	The X-Coordinate of where to place the String.
//				y		-	The Y-Coordinate of where to place the String.
//				*string	-	The String to print out.
//				...		-	The Variable Argument list.
//
//	Return	:	True if Successful.
bool Ogl_Draw::TextOutOrtho(int left, int right, int bottom, int top, float x, float y, const char *string, ...)
{
	//	Make sure fontdisplaylist and string are valid.
	if (!fontdisplaylist || !string)
		return false;

	char buffer[256] = {0};									//	Holds Our String.
	va_list	ap;												//	Pointer To List Of Arguments.

	va_start(ap, string);									//	Parses The String For Variables
	    vsprintf(buffer, string, ap);						//	And Converts Symbols To Actual Numbers
	va_end(ap);												//	Results Are Stored In buffer

	//	Set coordinate System.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);

	//	Drawing mode.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos2f(x,  y);
	glPushAttrib(GL_LIST_BIT);								//	Pushes The Display List Bits
	glListBase(fontdisplaylist);							//	Sets The Base Character to 32
	glCallLists(strlen(buffer), GL_UNSIGNED_BYTE, buffer);	//	Draws The Display List Text
	glPopAttrib();											//	Pops The Display List Bits

	//	Setup the aspect Ratio for Persepective Frustrum,
	float aspect = float(GetSystemMetrics(SM_CXSCREEN)) / float(GetSystemMetrics(SM_CYSCREEN));

	//	Set coordinate System.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	Can't use 0 for Near Clipping Plane.  This sets up our Perspective Frustrum for OpenGL.
	gluPerspective(90.0f, aspect, 0.01f, 1000.0f);

	//	Drawing mode.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//	Return Success.
	return true;
}
