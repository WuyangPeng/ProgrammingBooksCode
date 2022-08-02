#ifndef _WINMAINHEADER
#define _WINMAINHEADER


// Windows Header Files:
#include <windows.h>
#include <windef.h>
#include <commctrl.h>
#include <commdlg.h>
#include <wingdi.h> 

#define	_WINWIDTH	1024
#define	_WINHEIGHT	768

extern	bool	ShowTrails;
extern	bool	ShowVectors;
extern	bool	BasicChase;
extern	bool	BasicEvade;
extern	bool	InterceptChase;
extern	bool	PotentialChase;
extern	bool	Patrol;
extern	bool	ZigZag;


void	CopyBackBufferToWindow(void);
void	DrawLine(int x1, int y1, int x2, int y2, int thk, COLORREF clr);
void	DrawRectangle(RECT *r, int thk, COLORREF borderCLR, COLORREF fillCLR);
void	DrawEllipse(RECT *r, int thk, COLORREF clr);
void	ClearBackBuffer(void);
BOOL	IsKeyDown(short KeyCode);


#endif