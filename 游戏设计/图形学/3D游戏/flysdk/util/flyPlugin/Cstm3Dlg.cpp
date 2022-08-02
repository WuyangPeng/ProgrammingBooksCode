// cstm2dlg.cpp : implementation file
//

#include "stdafx.h"
#include "flyplugin.h"
#include "cstm3dlg.h"
#include "flypluginaw.h"
#include <shlobj.h>

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char str_num_classes[256];
extern char str_get_class_desc[512];
char *buf_img3=0;
extern BITMAPINFO bmi;

/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg dialog


CCustom3Dlg::CCustom3Dlg()
	: CAppWizStepDlg(CCustom3Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCustom3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom3Dlg)
	DDX_Control(pDX, IDC_FLYSDKPATH, m_flysdkpath);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom3Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	char str[256];

	m_flysdkpath.GetWindowText(str,255);
	Flypluginaw.m_Dictionary["FLYSDKPATH"]=str;

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCustom3Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom3Dlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BROWSEFLY, OnBrowsefly)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg message handlers

void CCustom3Dlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	RECT rect;
	GetClientRect(&rect);

	CBrush brush(RGB(96,96,96));
	rect.right=180;
	dc.FillRect(&rect,&brush);

	dc.SelectObject(GetStockObject(BLACK_PEN));

	dc.MoveTo(rect.right,0);
	dc.LineTo(rect.right,rect.bottom);

	if (buf_img3==0)
	{
	HRSRC res=FindResource(hInst,"IMG3","TEMPLATE");
	if (res)
		{
		HGLOBAL hg=LoadResource(hInst,res);
		if (hg)
			{
			buf_img3=(char *)LockResource(hg);
			if (buf_img3)
				{
				bmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
				bmi.bmiHeader.biWidth=128;
				bmi.bmiHeader.biHeight=128;
				bmi.bmiHeader.biPlanes=1;
				bmi.bmiHeader.biBitCount=24;
				bmi.bmiHeader.biCompression=BI_RGB;
				bmi.bmiHeader.biSizeImage=0;
				bmi.bmiHeader.biXPelsPerMeter=3600;
				bmi.bmiHeader.biYPelsPerMeter=3600; 
				bmi.bmiHeader.biClrUsed=0;     
				bmi.bmiHeader.biClrImportant=0; 
				}
			}
		}
	}
	if (buf_img3)
		SetDIBitsToDevice(dc.m_hDC,
			rect.right/2-64,32,128,128,
			0,0,0,128,
			&buf_img3[18],&bmi,DIB_RGB_COLORS);
}

void CCustom3Dlg::OnBrowsefly() 
{
    BROWSEINFO bi;
	char Buffer[MAX_PATH];
    LPITEMIDLIST pidlBrowse;
	LPMALLOC ppMalloc;
	
	SHGetMalloc( &ppMalloc );

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = 0;
    bi.pszDisplayName = Buffer;
	bi.lpszTitle = "Select the Fly3D SDK folder";
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;

    pidlBrowse = SHBrowseForFolder(&bi);

	if (pidlBrowse != NULL) 
		{  
        if (SHGetPathFromIDList(pidlBrowse, Buffer)) 
			{
			if (Buffer[0]!=0)
				if (Buffer[strlen(Buffer)-1]!='\\')
					strcat(Buffer,"\\");
            m_flysdkpath.SetWindowText(Buffer);
			}
		ppMalloc->Free(pidlBrowse);
		}
}

BOOL CCustom3Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();

	m_flysdkpath.SetWindowText(Flypluginaw.m_Dictionary["FLYSDKPATH"]);
	
	return TRUE;
}
