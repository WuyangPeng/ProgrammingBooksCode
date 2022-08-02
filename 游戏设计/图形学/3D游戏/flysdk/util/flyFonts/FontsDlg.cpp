// FontsDlg.cpp : implementation file
//

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "Fonts.h"
#include "FontsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int size=128,flag=0;

/////////////////////////////////////////////////////////////////////////////
// CFontsDlg dialog

CFontsDlg::CFontsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontsDlg)
	DDX_Control(pDX, IDC_SAVE, m_save);
	DDX_Control(pDX, IDC_256, m_256);
	DDX_Control(pDX, IDC_128, m_128);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontsDlg, CDialog)
	//{{AFX_MSG_MAP(CFontsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FONT, OnFont)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_256, On256)
	ON_BN_CLICKED(IDC_128, On128)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontsDlg message handlers

BOOL CFontsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	memset(&lf,0,sizeof(lf));
	
	if (size==128)
		m_128.SetState(1);
	else 
	{
		size=256;
		m_128.SetState(2);
	}

	m_save.EnableWindow(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFontsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC mydc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) mydc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		mydc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawBMP();
	}
}

HCURSOR CFontsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFontsDlg::OnFont() 
{
	CFontDialog	fd(&lf);

	if (fd.DoModal()==IDOK)
	{
		fd.GetCurrentFont( &lf );
		SetDlgItemText( IDC_FONTNAME, fd.GetFaceName());
		flag=1;
		m_save.EnableWindow(1);
		Invalidate(1);
	}
}

void CFontsDlg::DrawBMP()
{
	if (flag)
	{
	char str[2]=" ";
	CFont f;
	CSize len;
	int n;
	int x,y;
	CRect rect;
	GetClientRect(&rect);
	x=10;
	y=40;

	CPaintDC mydc(this);
	mydc.FillSolidRect(x,y,size,size,0 );

	mydc.SetTextColor(0xffffffff);
	f.CreateFontIndirect(&lf);
	mydc.SelectObject(f);

	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
		{
			n=' '+i+j*8;
			if (n>='A' && n<='Z')
				str[0]=n+(int)'a'-(int)'A';
			else str[0]=n;
			mydc.TextOut(x+2+i*size/8,y+j*size/8,str);
		}
	}
	CDialog::OnPaint();
}

void CFontsDlg::OnSave() 
{
	char str[2]=" ";
	CFont f;
	CSize len;
	int n;

//	CFileDialog fd(0,"tga",0,OFN_OVERWRITEPROMPT,"TGA files|*.tga||",this);
//	if (fd.DoModal()==IDOK)
	{

	FILE *fp=fopen( "fonts.tga","wb");
//	FILE *fp=fopen( fd.GetPathName(),"wb");
	if (fp)
	{
		unsigned char TGA_INI[18];
		CDC *mydc=GetDC();
		POINT p;

		int x,y;
		CRect rect;
		GetClientRect(&rect);
//		x=rect.right/2-size/2;
//		y=(rect.bottom-size)*2/3;
		x=20;
		y=40;

        memset(&TGA_INI[0],0,18);
        TGA_INI[12]=(unsigned char)(size%256);
        TGA_INI[13]=(unsigned char)(size/256);
        TGA_INI[14]=(unsigned char)(size%256);
        TGA_INI[15]=(unsigned char)(size/256);
        TGA_INI[2]=2;
        TGA_INI[16]=8*4;
        fwrite((char *)&TGA_INI[0],18,1,fp);

		for( p.y=size+y-1;p.y>=y;p.y-- )
			for( p.x=x;p.x<size+x;p.x++ )
			{
				COLORREF c=mydc->GetPixel(p);
				fwrite(&c,sizeof(c),1,fp);
			}

		fclose(fp);
		ReleaseDC(mydc);
	}

	fp=fopen("fonts.txt","wt");
/*	char str[256];
	strcpy(str,fd.GetPathName());
	if (strrchr(str,'.'))
		*strrchr(str,'.')=0;
	strcat(str,".txt");
	fp=fopen(str,"wt");*/
	if (fp)
	{
		CDC *mydc=GetDC();
		mydc->SetTextColor(0xffffffff);
		f.CreateFontIndirect(&lf);
		mydc->SelectObject(f);

		int i,j;
		for( j=0;j<8;j++ )
			for( i=0;i<8;i++ )
			{
			n=' '+i+j*8;
			if (n>='A' && n<='Z')
				str[0]=n+(int)'a'-(int)'A';
			else str[0]=n;
			len=mydc->GetTextExtent(str,1);
			fprintf(fp,"%i\n",(len.cx+2)/2);
			}
		ReleaseDC(mydc);
		fclose(fp);
	}
	}
}

void CFontsDlg::On256() 
{
	size=256;
	Invalidate(1);
	m_128.SetState(0);
	m_256.SetState(1);
}

void CFontsDlg::On128() 
{
	size=128;
	Invalidate(1);
	m_128.SetState(1);
	m_256.SetState(0);
}
