// VCFBuilder.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <initguid.h>
#include "VCFBuilder.h"
#include "DSAddIn.h"
#include "Commands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_DSAddIn, CDSAddIn)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCFBuilderApp

class CVCFBuilderApp : public CWinApp
{
public:
	CVCFBuilderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCFBuilderApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CVCFBuilderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CVCFBuilderApp

BEGIN_MESSAGE_MAP(CVCFBuilderApp, CWinApp)
	//{{AFX_MSG_MAP(CVCFBuilderApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CVCFBuilderApp object

CVCFBuilderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVCFBuilderApp construction

CVCFBuilderApp::CVCFBuilderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// CVCFBuilderApp initialization

BOOL CVCFBuilderApp::InitInstance()
{
	initApplicationKit();
	_Module.Init(ObjectMap, m_hInstance);
	return CWinApp::InitInstance();
}

int CVCFBuilderApp::ExitInstance()
{
	_Module.Term();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return _Module.GetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

// by exporting DllRegisterServer, you can use regsvr32.exe
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HRESULT hRes = S_OK;
	
	// Registers object, typelib and all interfaces in typelib
	hRes = _Module.RegisterServer(TRUE);
	if (FAILED(hRes))
		return hRes;

	// Register description of this add-in object in its own
	//  "/Description" subkey.
	// TODO:  If you add more add-ins to this module, you need
	//  to register all of their descriptions, each description
	//  in each add-in object's registry CLSID entry:
	// HKEY_CLASSES_ROOT\Clsid\{add-in CLSID}\Description="add-in description"
	_ATL_OBJMAP_ENTRY* pEntry = _Module.m_pObjMap;
	CRegKey key;
	LONG lRes = key.Open(HKEY_CLASSES_ROOT, _T("CLSID"));
	if (lRes == ERROR_SUCCESS)
	{
		USES_CONVERSION;
		LPOLESTR lpOleStr;
		StringFromCLSID(*pEntry->pclsid, &lpOleStr);
		LPTSTR lpsz = OLE2T(lpOleStr);

		lRes = key.Open(key, lpsz);
		if (lRes == ERROR_SUCCESS)
		{
			CString strDescription;
			strDescription.LoadString(IDS_VCFBUILDER_DESCRIPTION);
			key.SetKeyValue(_T("Description"), strDescription);
		}
		CoTaskMemFree(lpOleStr);
	}
	if (lRes != ERROR_SUCCESS)
		hRes = HRESULT_FROM_WIN32(lRes);

	return hRes;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT hRes = S_OK;
	_Module.UnregisterServer();
	return hRes;
}


/////////////////////////////////////////////////////////////////////////////
// Debugging support

// GetLastErrorDescription is used in the implementation of the VERIFY_OK
//  macro, defined in stdafx.h.

#ifdef _DEBUG

void GetLastErrorDescription(CComBSTR& bstr)
{
	CComPtr<IErrorInfo> pErrorInfo;
	if (GetErrorInfo(0, &pErrorInfo) == S_OK)
		pErrorInfo->GetDescription(&bstr);
}

#endif //_DEBUG
