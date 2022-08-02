// FourierDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fourier.h"
#include "FourierDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FourierDlg dialog


FourierDlg::FourierDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FourierDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(FourierDlg)
	m_terms = 4;
	//}}AFX_DATA_INIT
}


void FourierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FourierDlg)
	DDX_Text(pDX, IDC_EDIT2, m_terms);
	DDV_MinMaxUInt(pDX, m_terms, 1, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FourierDlg, CDialog)
	//{{AFX_MSG_MAP(FourierDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FourierDlg message handlers

void FourierDlg::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData(true);
	CDialog::OnOK();
}

void FourierDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(false);
	CDialog::OnCancel();
}
