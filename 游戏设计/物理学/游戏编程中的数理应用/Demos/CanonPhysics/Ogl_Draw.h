//	Ogl_Draw.h : Class that sets up an OpenGL Window.

#ifndef OGLDRAW_H
#define OGLDRAW_H

#include <windows.h>

class Ogl_Draw
{
	private:
		GLYPHMETRICSFLOAT glyph[256];		//	Storage for Information about the Outline Font Characters.

		int fontdisplaylist;				//	Holds the Font Display List.
		int outlinefontdlist;				//	Holds the Outline Font Display List.

	public:
		//	Default Constructor.
		Ogl_Draw();
		//	Destructor.
		~Ogl_Draw();

		//	ChooseFont : Choose the Font to use when printing strings to the Screen.
		//
		//	Input	:	*fontname	-	The Font to use.  Default is Courier New.
		//				fontheight	-	How big do you want the font to be.
		//
		//	Return	:	True if Successful.
		bool ChooseFont(HDC hDC, int fontheight, char *fontname);

		//	TextOut : Simplest form of the TextOut function.  You just pass in the string to print to the
		//			  screen.  You have to specify the color and position with calls to glColor3ub() and
		//			  glRasterPos3f().	This function can be used much like sprintf.
		//
		//	Input	:	*string		-	The String to print out.
		//				...			-	The Variable Argument list.  This is for functionality like sprintf();
		//
		//	Return	:	True if Successful.
		bool TextOut(const char *string, ...);

		//	TextOut : Prints the string at the specified position and using the specified color.  This uses
		//			  arrays for the positioning and coloring.
		//
		//	Input	:	pos[]	-	The Position Array.
		//				color[]	-	The Color Array.
		//				*string	-	The String to print out.
		//				...		-	The Variable Argument list.
		//
		//	Return	:	True if Successful.
		bool TextOut(float pos[3], int color[3], const char *string, ...);

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
		bool TextOut(float x, float y, float z, int r, int g, int b, const char *string, ...);

		//	TextOut : Prints the string at the specified position using glOrtho2D.
		//
		//	Input	:	x		-	The X-Coordinate of where to place the String.
		//				y		-	The Y-Coordinate of where to place the String.
		//				*string	-	The String to print out.
		//				...		-	The Variable Argument list.
		//
		//	Return	:	True if Successful.
		bool TextOut(float x, float y, const char *string, ...);
		bool TextOutOrtho(int left, int right, int bottom, int top, float x, float y, const char *string, ...);

		//	TextOut3D : Output a String in 3D.  The Color can be set with glColor3ub and you can
		//				move it about with glTranslatef() and such.
		//
		//	Input	:	*string	-	The String to print out.
		//				...		-	The Variable Argument list.
		//
		//	Return	:	True if Successful.
		bool TextOut3D(const char *string, ...);
};

#endif
