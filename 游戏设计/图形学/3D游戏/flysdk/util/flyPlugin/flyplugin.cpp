// flyplugin.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "flyplugin.h"
#include "flypluginaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE FlypluginDLL = { NULL, NULL };

HINSTANCE hInst=0;

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInst=hInstance;
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("FLYPLUGIN.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(FlypluginDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(FlypluginDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&Flypluginaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("FLYPLUGIN.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(FlypluginDLL);
	}
	return 1;   // ok
}
