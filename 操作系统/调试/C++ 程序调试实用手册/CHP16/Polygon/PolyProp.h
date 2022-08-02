// PolyProp.h : Declaration of the CPolyProp

#ifndef __POLYPROP_H_
#define __POLYPROP_H_

#include "resource.h"       // main symbols
#include "Polygon.h"

EXTERN_C const CLSID CLSID_PolyProp;

/////////////////////////////////////////////////////////////////////////////
// CPolyProp
class ATL_NO_VTABLE CPolyProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPolyProp, &CLSID_PolyProp>,
	public IPropertyPageImpl<CPolyProp>,
	public CDialogImpl<CPolyProp>
{
public:
	CPolyProp() 
	{
		m_dwTitleID = IDS_TITLEPolyProp;
		m_dwHelpFileID = IDS_HELPFILEPolyProp;
		m_dwDocStringID = IDS_DOCSTRINGPolyProp;
	}

	enum {IDD = IDD_POLYPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_POLYPROP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPolyProp) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CPolyProp)
	CHAIN_MSG_MAP(IPropertyPageImpl<CPolyProp>)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void)
	{
		ATLTRACE(_T("CPolyProp::Apply\n"));
		for (UINT i = 0; i < m_nObjects; i++)
		{
			CComQIPtr<IPolyCtl, &IID_IPolyCtl> pPoly(m_ppUnk[i]);
			short nSides = (short)GetDlgItemInt(IDC_SIDES);
			if FAILED(pPoly->put_Sides(nSides))
			{
				CComPtr<IErrorInfo> pError;
				CComBSTR strError;
				GetErrorInfo(0, &pError);
				pError->GetDescription(&strError);
				MessageBox("Error - Enter 3 to 10 sides",
					       "Error Message", MB_ICONEXCLAMATION);
				return E_FAIL;
			}
		}
		m_bDirty = FALSE;
		return S_OK;
	}
};

#endif //__POLYPROP_H_
