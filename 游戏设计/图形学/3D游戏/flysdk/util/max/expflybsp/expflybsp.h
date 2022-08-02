// flyexp.h: interface for the flyexp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLYEXP_H__E9862694_B5E9_11D1_9E60_004F4902C0C3__INCLUDED_)
#define AFX_FLYEXP_H__E9862694_B5E9_11D1_9E60_004F4902C0C3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "max.h"
#include "resource.h"

class flyexp : public SceneExport
{
public:
#ifdef MAX3
	int DoExport(const TCHAR *,ExpInterface *,Interface *, BOOL=FALSE, DWORD options=0);	// max 3.x
#endif
#ifdef MAX2
	int DoExport(const TCHAR *,ExpInterface *,Interface *, BOOL=FALSE);						// max 2.x
#endif
#ifdef MAX1
	int DoExport(const TCHAR *,ExpInterface *ei,Interface *i);								// max 1.x
#endif

	flyexp();
	~flyexp();

	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
};

#endif // !defined(AFX_FLYEXP_H__E9862694_B5E9_11D1_9E60_004F4902C0C3__INCLUDED_)
