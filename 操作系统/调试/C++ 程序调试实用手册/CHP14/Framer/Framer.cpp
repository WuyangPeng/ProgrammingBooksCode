// Framer.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Framer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CFramerApp

BEGIN_MESSAGE_MAP(CFramerApp, CWinApp)
	//{{AFX_MSG_MAP(CFramerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFramerApp construction

CFramerApp::CFramerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFramerApp object

CFramerApp theApp;

__declspec( dllexport ) void WINAPI ThickRectangle(CDC* pDC,
												   int x1,
												   int y1,
												   int x2,
												   int y2,
												   int t)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  
  CBrush newbrush;
  CBrush* oldbrush; 

  pDC->Rectangle(x1,y1,x2,y2);
  pDC->Rectangle(x1+t,y1+t,x2-t,y2-t);
  newbrush.CreateSolidBrush(RGB(255,255,0));
  oldbrush=pDC->SelectObject(&newbrush);
  pDC->FloodFill(x1+(t/2),y1+(t/2),RGB(0,0,0));
  pDC->SelectObject(oldbrush);
  newbrush.DeleteObject();
}

__declspec( dllexport ) void WINAPI ThickEllipse(CDC* pDC,
												 int x1,
												 int y1,
												 int x2,
												 int y2,
												 int t)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  
  CBrush newbrush;
  CBrush* oldbrush; 

  pDC->Ellipse(x1,y1,x2,y2);
  pDC->Ellipse(x1+t,y1+t,x2-t,y2-t);
  newbrush.CreateSolidBrush(RGB(255,0,0));
  oldbrush=pDC->SelectObject(&newbrush);
  pDC->FloodFill(x1+(t/2),y1 + ((y2 - y1)/2),RGB(0,0,0));
  pDC->SelectObject(oldbrush);
  newbrush.DeleteObject();
}

__declspec( dllexport ) void WINAPI ThickPixel(CDC* pDC,
											   int x1,
											   int y1)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  
  CPen newpen;
  CPen* oldpen; 

  pDC->SetPixel(x1,y1,0L);
  newpen.CreatePen(PS_SOLID,2,RGB(200,200,200));
  oldpen=pDC->SelectObject(&newpen);
  pDC->MoveTo(x1-5,y1);
  pDC->LineTo(x1-1,y1);
  pDC->MoveTo(x1+1,y1);
  pDC->LineTo(x1+5,y1);
  pDC->MoveTo(x1,y1-5);
  pDC->LineTo(x1,y1-1);
  pDC->MoveTo(x1,y1+1);
  pDC->LineTo(x1,y1+5);
  pDC->SelectObject(oldpen);
  newpen.DeleteObject();
}




