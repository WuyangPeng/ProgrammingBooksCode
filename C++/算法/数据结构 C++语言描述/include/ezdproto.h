#ifndef _EZ_DRAW_PROTOTYPES_
#define _EZ_DRAW_PROTOTYPES_

#include "EzDraw.h"

#ifdef __cplusplus
extern "C" 
{
#endif

typedef struct tag_ezdFunctions
	{
	HINSTANCE	hInst;
	EZDBOOL		(EZDCDECL* ezdInitialize)(void);
	void		   (EZDCDECL* ezdCleanUp)(void);
	EZDHANDLE	(EZDCDECL* ezdDrawLine)(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2);
	EZDHANDLE	(EZDCDECL* ezdDrawRectangle)(EZDFLOAT fX1, EZDFLOAT fY1, EZDFLOAT fX2, EZDFLOAT fY2);
	EZDHANDLE	(EZDCDECL* ezdDrawCircle)(EZDFLOAT fX, EZDFLOAT fY, EZDFLOAT fR);
	EZDHANDLE	(EZDCDECL* ezdDrawPoint)(EZDFLOAT fX, EZDFLOAT fY);
	EZDHANDLE	(EZDCDECL* ezdDrawPolygon)(EZDULONG lCount, EZDLPFLOAT pfXarray, EZDLPFLOAT pfYarray);
	EZDHANDLE	(EZDCDECL* ezdDrawText)(EZDLPCHAR szText, EZDFLOAT fX, EZDFLOAT fY);
	EZDBOOL		(EZDCDECL* ezdDeleteShape)(EZDHANDLE hShape);
	EZDCOLORVAL	(EZDCDECL* ezdSetColor)(EZDCOLORVAL color);
	EZDCHAR		(EZDCDECL* ezdWaitForKeyPress)();
	} EZDFUNCS, *LPEZDFUNCS;

EZDFUNCS EZDEXTDATA ezdFuncs;
#define EZDFUNC_ORDNAL ((LPCTSTR)(9))

#ifdef __cplusplus 
}
#endif
#endif
