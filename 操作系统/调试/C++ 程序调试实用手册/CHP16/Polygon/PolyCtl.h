// PolyCtl.h : Declaration of the CPolyCtl

#ifndef __POLYCTL_H_
#define __POLYCTL_H_

#include <math.h>
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "PolygonCP.h"


/////////////////////////////////////////////////////////////////////////////
// CPolyCtl
class ATL_NO_VTABLE CPolyCtl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CPolyCtl, IPolyCtl, &IID_IPolyCtl, &LIBID_POLYGONLib>,
	public CComControl<CPolyCtl>,
	public IPersistStreamInitImpl<CPolyCtl>,
	public IOleControlImpl<CPolyCtl>,
	public IOleObjectImpl<CPolyCtl>,
	public IOleInPlaceActiveObjectImpl<CPolyCtl>,
	public IViewObjectExImpl<CPolyCtl>,
	public IOleInPlaceObjectWindowlessImpl<CPolyCtl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPolyCtl>,
	public IPersistStorageImpl<CPolyCtl>,
	public ISpecifyPropertyPagesImpl<CPolyCtl>,
	public IQuickActivateImpl<CPolyCtl>,
	public IDataObjectImpl<CPolyCtl>,
	public IProvideClassInfo2Impl<&CLSID_PolyCtl, &DIID__IPolyCtlEvents, &LIBID_POLYGONLib>,
	public IPropertyNotifySinkCP<CPolyCtl>,
	public CComCoClass<CPolyCtl, &CLSID_PolyCtl>,
	public CProxy_IPolyCtlEvents< CPolyCtl >
{
public:
	CPolyCtl()
	{
		m_nSides = 4;							//initial rectangle
		m_clrFillColor = RGB(0xFF, 0xFF, 0);	//use yellow fill
	}

DECLARE_REGISTRY_RESOURCEID(IDR_POLYCTL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPolyCtl)
	COM_INTERFACE_ENTRY(IPolyCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CPolyCtl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("FillColor", DISPID_FILLCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Sides", 1, CLSID_PolyProp)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CPolyCtl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IPolyCtlEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CPolyCtl)
	CHAIN_MSG_MAP(CComControl<CPolyCtl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IPolyCtl,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IPolyCtl
public:
	STDMETHOD(get_Sides)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Sides)(/*[in]*/ short newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di);
//	{
//		RECT& rc = *(RECT*)di.prcBounds;
//		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
//
//		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
//		LPCTSTR pszText = _T("ATL 3.0 : PolyCtl");
//		TextOut(di.hdcDraw, 
//			(rc.left + rc.right) / 2, 
//			(rc.top + rc.bottom) / 2, 
//			pszText, 
//			lstrlen(pszText));
//
//		return S_OK;
//	}
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam,
		                  LPARAM lParam, BOOL& bHandled);
	short m_nSides;
	OLE_COLOR m_clrFillColor;
	POINT m_arrPoint[10];
};

#endif //__POLYCTL_H_
