// flyConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "flyConfig.h"
#include "flyConfigDlg.h"
#include <gl\gl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDC *cdc=0;
HGLRC hglrc=0;

PIXELFORMATDESCRIPTOR rendermodes[256];
DEVMODE	videomodes[256];
int numrendermodes=0;
int selrendermode=0;
int numvideomodes=0;
int selvideomode=0;
int colorbits=0;
int depthbits=0;
int stencilbits=0;
float brightness=1.0f;

void FlyGetProfile(LPTSTR section, LPTSTR key, LPBYTE lpData, DWORD cbData)
{
	HKEY key1,key2,key3,key4;

	if (ERROR_SUCCESS==RegOpenKeyEx(HKEY_CURRENT_USER,"Software",0,KEY_READ,&key1))
	{
		if (ERROR_SUCCESS==RegOpenKeyEx(key1,"Paralelo",0,KEY_READ,&key2))
		{
			if (ERROR_SUCCESS==RegOpenKeyEx(key2,"Fly3D",0,KEY_READ,&key3))
			{
				if (ERROR_SUCCESS==RegOpenKeyEx(key3,section,0,KEY_READ,&key4))
				{
					RegQueryValueEx(key4, key, 0, 0, lpData, &cbData);
					RegCloseKey(key4);
				}
				RegCloseKey(key3);
			}
			RegCloseKey(key2);
		}
		RegCloseKey(key1);
	}
}

void FlyWriteProfile(LPTSTR section, LPCTSTR key, DWORD dwType, CONST BYTE *lpData, DWORD cbData)
{
	HKEY key1,key2,key3,key4;
	DWORD d;

	if (ERROR_SUCCESS==RegOpenKeyEx(HKEY_CURRENT_USER,"Software",0,KEY_READ,&key1))
	{
		if (ERROR_SUCCESS==RegCreateKeyEx(key1,"Paralelo",0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&key2,&d))
		{
			if (ERROR_SUCCESS==RegCreateKeyEx(key2,"Fly3D",0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&key3,&d))
			{
				if (ERROR_SUCCESS==RegCreateKeyEx(key3, section,0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&key4,&d))
				{
					RegSetValueEx(key4, key, 0, dwType, lpData, cbData);
					RegCloseKey(key4);
				}
				RegCloseKey(key3);
			}
			RegCloseKey(key2);
		}
		RegCloseKey(key1);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlyConfigDlg dialog

CFlyConfigDlg::CFlyConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlyConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlyConfigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlyConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlyConfigDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlyConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CFlyConfigDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_EN_KILLFOCUS(IDC_BRIGHTNESS, OnKillfocusBrightness)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlyConfigDlg message handlers

BOOL CFlyConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	FlyGetProfile("Settings","videomode", (unsigned char *)&selvideomode, sizeof(int));
	FlyGetProfile("Settings","rendermode", (unsigned char *)&selrendermode, sizeof(int));
	FlyGetProfile("Settings","brightness", (unsigned char *)&brightness, sizeof(float));
	init();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFlyConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFlyConfigDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CFlyConfigDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CFlyConfigDlg::init_gl()
{
	int pfd=SendDlgItemMessage(IDC_RENDERMODES,CB_GETITEMDATA,selrendermode,0);
	if (SetPixelFormat(cdc->GetSafeHdc(), pfd, &rendermodes[selrendermode]) == FALSE) 
	{
		MessageBox("Could not set pixel format!","Fly3D Config",MB_OK|MB_ICONEXCLAMATION);
		return 0;
	}

	hglrc = wglCreateContext( cdc->GetSafeHdc() );
	if (hglrc==0)
	{
		MessageBox("Could not create rendring context!","Fly3D Config",MB_OK|MB_ICONEXCLAMATION);
		return 0;
	}

	wglMakeCurrent( cdc->GetSafeHdc(), hglrc );

	char *p;
	p=(char *)glGetString(GL_RENDERER);
	SetDlgItemText(IDC_RENDER,p);
	p=(char *)glGetString(GL_VENDOR);
	SetDlgItemText(IDC_VENDOR,p);
	p=(char *)glGetString(GL_VERSION);
	SetDlgItemText(IDC_VERSION,p);
	p=(char *)glGetString(GL_EXTENSIONS);
	if (p==0||p[0]==0)
		return 1;

	SendDlgItemMessage(IDC_EXTENSIONS,LB_RESETCONTENT,0,0);
	char buf[4096];
	strcpy(buf,p);
	char *c1=buf,*c2;
	do{
		c2=strchr(c1,' ');
		if (c2)
			*c2=0;
		SendDlgItemMessage(IDC_EXTENSIONS,LB_ADDSTRING,0,(DWORD)c1);
		if (c2==0)
			break;
		c1=c2+1;
	} while(*c1!=0);

	char str[256];
	
	int i=1,j;
	if (p!=0&&strstr(p,"GL_ARB_multitexture"))
		glGetIntegerv(0x84E2,&i);
	sprintf(str,"NTexUnits: %i   ",i);
	strcpy(buf,str);

	glGetIntegerv(GL_MAX_LIGHTS,&i);
	sprintf(str,"NLights: %i\r\n",i);
	strcat(buf,str);

	glGetIntegerv(GL_DEPTH_BITS,&i);
	sprintf(str,"Depth: %i   ",i);
	strcat(buf,str);

	glGetIntegerv(GL_STENCIL_BITS,&i);
	sprintf(str,"Stencil: %i   ",i);
	strcat(buf,str);

	glGetIntegerv(GL_ACCUM_ALPHA_BITS,&i);
	j=i;
	glGetIntegerv(GL_ACCUM_RED_BITS,&i);
	j+=i;
	glGetIntegerv(GL_ACCUM_BLUE_BITS,&i);
	j+=i;
	glGetIntegerv(GL_ACCUM_GREEN_BITS,&i);
	j+=i;
	sprintf(str,"Accum: %i   ",j);
	strcat(buf,str);

	glGetIntegerv(GL_ALPHA_BITS,&i);
	sprintf(str,"Alpha: %i",i);
	strcat(buf,str);
	
	SetDlgItemText(IDC_INFO,buf);

	return 1;
}

void CFlyConfigDlg::free_gl()
{
	if (hglrc==0)
		return;

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	hglrc=0;
}

void CFlyConfigDlg::free()
{
	ReleaseDC(cdc);
	cdc=0;
	numvideomodes=0;
	numrendermodes=0;
	selrendermode=0;
}

void CFlyConfigDlg::init()
{
	char str[256];
	int i,j,k,numaccel;

	cdc=GetDC();
	colorbits=cdc->GetDeviceCaps(BITSPIXEL);
	sprintf(str,"%i bits/pixel",colorbits);
	SetDlgItemText(IDC_COLORDEPTH,str);
	sprintf(str,"%.2f",brightness);
	SetDlgItemText(IDC_BRIGHTNESS,str);
	
	SendDlgItemMessage(IDC_VIDEOMODES,CB_RESETCONTENT,0,0);
	SendDlgItemMessage(IDC_RENDERMODES,CB_RESETCONTENT,0,0);
	SetDlgItemText(IDC_RENDER,"");
	SetDlgItemText(IDC_VENDOR,"");
	SetDlgItemText(IDC_VERSION,"");
	GetDlgItem(IDOK)->EnableWindow(0);
	GetDlgItem(IDC_CLOSE)->EnableWindow(0);

	i=0;
	while (EnumDisplaySettings(NULL,i,&videomodes[numvideomodes]))
	{
		if ((int)videomodes[numvideomodes].dmBitsPerPel==colorbits)
		{
			if (videomodes[numvideomodes].dmDisplayFrequency==0)
				sprintf(str,"Resolution: %ix%i",
					videomodes[numvideomodes].dmPelsWidth,videomodes[numvideomodes].dmPelsHeight);
			else
				sprintf(str,"Resolution: %ix%i   Refresh: %i ",
					videomodes[numvideomodes].dmPelsWidth,videomodes[numvideomodes].dmPelsHeight,videomodes[numvideomodes].dmDisplayFrequency);
			SendDlgItemMessage(IDC_VIDEOMODES,CB_ADDSTRING,0,(LPARAM)str);
			numvideomodes++;
		}
		i++;
	}

	numaccel=0;
	i=1;
	j=DescribePixelFormat(cdc->GetSafeHdc(),i,sizeof(PIXELFORMATDESCRIPTOR),&rendermodes[i]);
	numrendermodes=0;
	while(i<j)
	{
		DescribePixelFormat(cdc->GetSafeHdc(),i,sizeof(PIXELFORMATDESCRIPTOR),&rendermodes[numrendermodes]);
		if (rendermodes[numrendermodes].iPixelType==0 && 
			(rendermodes[numrendermodes].dwFlags&PFD_DOUBLEBUFFER) &&
			rendermodes[numrendermodes].cColorBits==colorbits)
			{
			sprintf(str,"%s  Depth:%i  Stencil:%i  Accum:%i  Alpha:%i" ,
				(rendermodes[numrendermodes].dwFlags&PFD_GENERIC_FORMAT)?"Genetric":"Accelerated",
				rendermodes[numrendermodes].cDepthBits,
				rendermodes[numrendermodes].cStencilBits,
				rendermodes[numrendermodes].cAccumBits,
				rendermodes[numrendermodes].cAlphaBits);
			if ((rendermodes[numrendermodes].dwFlags&PFD_GENERIC_FORMAT)==0)
				numaccel++;
			k=SendDlgItemMessage(IDC_RENDERMODES,CB_ADDSTRING,0,(LPARAM)str);
			SendDlgItemMessage(IDC_RENDERMODES,CB_SETITEMDATA,k,i);
			numrendermodes++;
			}
		i++;
	}

	if (colorbits<16)
	{
		GetDlgItem(IDC_TEST)->EnableWindow(0);
		MessageBox("Current color depth is not supported!\nMust be in 16, 24 or 32 bits/pixel video mode.","Fly3D Config",MB_ICONEXCLAMATION);
	}
	else GetDlgItem(IDC_TEST)->EnableWindow(1);
	
	if (selvideomode<numvideomodes)
		SendDlgItemMessage(IDC_VIDEOMODES,CB_SETCURSEL,selvideomode,0);
	if (selrendermode<numrendermodes)
		SendDlgItemMessage(IDC_RENDERMODES,CB_SETCURSEL,selrendermode,0);
}

void CFlyConfigDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	free_gl();
	free();
}


void CFlyConfigDlg::OnOK() 
{
	selvideomode=SendDlgItemMessage(IDC_VIDEOMODES,CB_GETCURSEL,1,0);
	selrendermode=SendDlgItemMessage(IDC_RENDERMODES,CB_GETCURSEL,1,0);

	char str[256];
	GetDlgItemText(IDC_BRIGHTNESS,str,255);
	sscanf(str,"%f",&brightness);

	if (rendermodes[selrendermode].dwFlags&PFD_GENERIC_FORMAT)
		MessageBox("A generic (not accelerated) render mode has been selected.\nRendering in software will make game play very slow.","Fly3D Config",MB_ICONINFORMATION);

	FlyWriteProfile("Settings","videomode", REG_DWORD, (unsigned char *)&selvideomode, sizeof(int));	
	FlyWriteProfile("Settings","rendermode", REG_DWORD, (unsigned char *)&selrendermode, sizeof(int));	
	FlyWriteProfile("Settings","brightness", REG_DWORD, (unsigned char *)&brightness, sizeof(float));	
	FlyWriteProfile("Settings","colorbits", REG_DWORD, (unsigned char *)&colorbits, sizeof(int));	

	EndDialog(IDOK);
}

void CFlyConfigDlg::OnTest() 
{
	selvideomode=SendDlgItemMessage(IDC_VIDEOMODES,CB_GETCURSEL,1,0);
	selrendermode=SendDlgItemMessage(IDC_RENDERMODES,CB_GETCURSEL,1,0);
	GetDlgItem(IDC_VIDEOMODES)->EnableWindow(0);
	GetDlgItem(IDC_RENDERMODES)->EnableWindow(0);
	GetDlgItem(IDC_COLORDEPTH)->EnableWindow(0);
	GetDlgItem(IDC_BRIGHTNESS)->EnableWindow(0);
	GetDlgItem(IDC_TEST)->EnableWindow(0);
	GetDlgItem(IDOK)->EnableWindow(1);
	GetDlgItem(IDC_CLOSE)->EnableWindow(1);
	
	free_gl();
	init_gl();	
}

LRESULT CFlyConfigDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message==WM_DISPLAYCHANGE)	
	{
		EndDialog(IDOK);
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CFlyConfigDlg::OnCancel() 
{
	EndDialog(IDCANCEL);
}

void CFlyConfigDlg::OnClose() 
{
	EndDialog(IDOK);
}


void CFlyConfigDlg::OnKillfocusBrightness() 
{
	char str[256];
	float f=0;
	GetDlgItemText(IDC_BRIGHTNESS,str,255);
	sscanf(str,"%f",&f);
	sprintf(str,"%.2f",f);
	SetDlgItemText(IDC_BRIGHTNESS,str);
}
