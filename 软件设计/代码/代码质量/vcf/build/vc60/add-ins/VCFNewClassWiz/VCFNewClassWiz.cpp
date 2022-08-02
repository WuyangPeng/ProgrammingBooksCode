// VCFNewClassWiz.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include <afxdllx.h>

#include <initguid.h>
#include "VCFNewClassWiz.h"

#include "VCFNewClassWizAddin.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_VCFNewClassWiz, CVCFNewClassWiz)
END_OBJECT_MAP()

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE VCFNewClassWizDLL = { NULL, NULL };

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("VCFNEWCLASSWIZ.DLL Initializing!\n");
		
		if (!AfxInitExtensionModule(VCFNewClassWizDLL, hInstance))
			return 0;

		if ( !AfxInitRichEdit() )
			return 0;

		new CDynLinkLibrary(VCFNewClassWizDLL);

     _Module.Init(ObjectMap, hInstance, &LIBID_VCFNEWCLASSWIZLib);
     DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("VCFNEWCLASSWIZ.DLL Terminating!\n");
		AfxTermExtensionModule(VCFNewClassWizDLL);

       _Module.Term();
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}

