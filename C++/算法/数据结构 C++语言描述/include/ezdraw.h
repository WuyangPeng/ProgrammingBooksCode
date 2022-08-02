#ifndef _EZ_DRAW_
#define _EZ_DRAW_

#ifdef __cplusplus
extern "C" 
{
#endif

#if defined _WIN32 && defined _MSC_VER && !defined _EZDNODECLSPEC
#define EZDFAR
#define EZDEXPORT _declspec(dllexport)
#define EZDIMPORT _declspec(dllimport)
#define EZDCDECL __stdcall
#elif !defined _WIN32                         
#define EZDFAR __far
#define EZDEXPORT __far __export __pascal
#define EZDIMPORT __far __export __pascal
#define EZDCDECL
#else
#define EZDFAR
#define EZDEXPORT
#define EZDIMPORT
#define EZDCDECL __stdcall
#endif

#define EXTERN extern

#ifdef _EZDRAWDLL_
#define EZDEXTERNAL EZDEXPORT EZDCDECL
#define EZDEXTDATA EZDEXPORT EXTERN
#else
#if defined _MSC_VER && !defined _EZDNODECLSPEC
#pragma comment(lib, "Ezd32m.lib")
#endif
#define EZDEXTERNAL EZDIMPORT EZDCDECL
#define EZDEXTDATA EZDIMPORT EXTERN
#endif

typedef char EZDCHAR;
typedef const EZDCHAR* EZDLPCHAR;
typedef int EZDBOOL;
typedef EZDBOOL EZDFAR* EZDLPBOOL;

#define EZDTRUE (1==1)
#define EZDFALSE (!EZDTRUE)

typedef unsigned char EZDBYTE;
typedef EZDBYTE EZDFAR* EZDLPBYTE;
typedef short EZDWORD;
typedef EZDWORD EZDFAR* EZDLPWORD;
typedef unsigned long EZDDWORD;
typedef EZDDWORD EZDFAR* EZDLPDWORD;
typedef int EZDINT;
typedef EZDINT EZDFAR* EZDLPINT;
typedef unsigned int EZDUINT;
typedef EZDUINT EZDFAR* EZDLPUINT;
typedef long EZDLONG;
typedef EZDLONG EZDFAR* EZDLPLONG;
typedef unsigned long EZDULONG;
typedef EZDULONG EZDFAR* EZDLPULONG;
typedef short EZDSHORT;
typedef EZDSHORT EZDFAR* EZDLPSHORT;
typedef unsigned short EZDUSHORT;
typedef EZDUSHORT EZDFAR* EZDLPUSHORT;
typedef double EZDFLOAT;
typedef EZDFLOAT EZDFAR* EZDLPFLOAT;
typedef const EZDFLOAT EZDFAR* EZDCLPFLOAT;
typedef EZDULONG EZDCOLORVAL;
typedef EZDCOLORVAL EZDFAR* EZDLPCOLORAL;
typedef EZDULONG EZDHANDLE;

#define EZDCOLOR(r,g,b) ((EZDCOLORVAL)(((EZDBYTE)(r)|((EZDWORD)((EZDBYTE)(g))<<8))|(((EZDDWORD)(EZDBYTE)(b))<<16)))

enum ezdColor {
	ezdWhite			= EZDCOLOR(0xff, 0xff, 0xff),
	ezdBlue				= EZDCOLOR(0x00, 0x00, 0xf0),
	ezdTeal     		= EZDCOLOR(0x00, 0x80, 0x80),
	ezdGreen			= EZDCOLOR(0x00, 0xc0, 0x00),
	ezdTurquoise		= EZDCOLOR(0x43, 0xc6, 0xdb),
	ezdDarkGray			= EZDCOLOR(0x7a, 0x7a, 0x7a),
	ezdBrown	   		= EZDCOLOR(0x98, 0x05, 0x17),
	ezdPurple   		= EZDCOLOR(0xa4, 0x00, 0xd7),
	ezdLightBlue		= EZDCOLOR(0xb5, 0xda, 0xff),
	ezdLightGray		= EZDCOLOR(0xdc, 0xdc, 0xdc),
	ezdGold         	= EZDCOLOR(0xd4, 0xa0, 0x17),
	ezdRed				= EZDCOLOR(0xff, 0x00, 0x00),
	ezdOrange			= EZDCOLOR(0xf8, 0x7a, 0x17),
	ezdPink				= EZDCOLOR(0xfa, 0xaf, 0xbe),
	ezdYellow			= EZDCOLOR(0xff, 0xff, 0x00),
	ezdBlack			= EZDCOLOR(0x00, 0x00, 0x00)
};
enum ezdOrigin {
	ezdAtPoint = 0,
	ezdCenter,
	};

enum ezdMapMode {
	ezdIsotropic = 0,
	ezdAnisotropic = 1
	};

EZDBOOL EZDEXTERNAL ezdInitialize(void);
void EZDEXTERNAL ezdCleanUp(void);
EZDHANDLE EZDEXTERNAL ezdDrawLine(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2);
EZDHANDLE EZDEXTERNAL ezdDrawRectangle(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2);
EZDHANDLE EZDEXTERNAL ezdDrawCircle(EZDFLOAT fX, EZDFLOAT fY, EZDFLOAT fR);
EZDHANDLE EZDEXTERNAL ezdDrawPoint(EZDFLOAT fX, EZDFLOAT fY);
EZDHANDLE EZDEXTERNAL ezdDrawPolygon(EZDULONG lCount, EZDCLPFLOAT pfXarray, EZDCLPFLOAT pfYarray);
EZDHANDLE EZDEXTERNAL ezdDrawText(EZDLPCHAR szText, EZDFLOAT fX, EZDFLOAT fY);
EZDBOOL EZDEXTERNAL ezdDeleteShape(EZDHANDLE hShape);
EZDCOLORVAL EZDEXTERNAL ezdSetColor(EZDCOLORVAL color);
EZDCHAR EZDEXTERNAL ezdWaitForKeyPress();
EZDFLOAT EZDEXTERNAL ezdGetOriginX();
EZDFLOAT EZDEXTERNAL ezdGetOriginY();
ezdOrigin EZDEXTERNAL ezdGetOriginType();
EZDBOOL EZDEXTERNAL ezdSetOriginType(EZDINT iMode);
EZDBOOL EZDEXTERNAL ezdSetOrigin(EZDFLOAT fX, EZDFLOAT fY, ezdOrigin Origin);
EZDFLOAT EZDEXTERNAL ezdGetViewportWidth();
EZDFLOAT EZDEXTERNAL ezdGetViewportHeight();
EZDBOOL EZDEXTERNAL ezdSetViewport(EZDFLOAT fX, EZDFLOAT fY);
ezdMapMode EZDEXTERNAL ezdGetMapMode();
EZDBOOL EZDEXTERNAL ezdSetMapMode(EZDINT iMode);
EZDBOOL EZDEXTERNAL ezdGetForceAspect();
EZDBOOL EZDEXTERNAL ezdSetForceAspect(EZDBOOL bForce);
EZDBOOL EZDEXTERNAL ezdClearDrawSurface();
EZDBOOL EZDEXTERNAL ezdKeyPress();
EZDBOOL EZDEXTERNAL ezdWait(EZDUINT uiMiliseconds);

#ifdef __cplusplus
}
#endif
#endif
