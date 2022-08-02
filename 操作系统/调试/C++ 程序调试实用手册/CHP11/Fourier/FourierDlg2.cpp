// FourierDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "Fourier.h"
#include "FourierDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FourierDlg2 dialog


FourierDlg2::FourierDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(FourierDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(FourierDlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void FourierDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FourierDlg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FourierDlg2, CDialog)
	//{{AFX_MSG_MAP(FourierDlg2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FourierDlg2 message handlers

// WHM - added code to message handlers
// to handle OK and CANCEL buttons 

void FourierDlg2::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	CDialog::OnOK();
}

void FourierDlg2::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(false);
	CDialog::OnCancel();
}


// WHM added following to process button selections

void FourierDlg2::OnRadio1() 
{
	// TODO: Add your control notification handler code here
    // WHM - sets red button to true
	m_check1 = true;
	m_check2 = false;
	m_check3 = false;
}

void FourierDlg2::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	// WHM - sets green button to true
	m_check1 = false;
	m_check2 = true;
	m_check3 = false;
}

void FourierDlg2::OnRadio3() 
{
	// TODO: Add your control notification handler code here
    // WHM - sets blue button to true
	m_check1 = false;
	m_check2 = false;
	m_check3 = true;
}
