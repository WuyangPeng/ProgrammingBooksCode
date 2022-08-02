// PenDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "PenDialog.h"


// CPenDialog dialog

IMPLEMENT_DYNAMIC(CPenDialog, CDialog)

CPenDialog::CPenDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPenDialog::IDD, pParent)
  , m_PenWidth(0)
{

}

CPenDialog::~CPenDialog()
{
}

void CPenDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_CBIndex(pDX, IDC_PENWIDTH_COMBO, m_PenWidth);
	DDV_MinMaxInt(pDX, m_PenWidth, 0, 5);
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialog)
END_MESSAGE_MAP()


// CPenDialog message handlers


BOOL CPenDialog::OnInitDialog()
{
  CDialog::OnInitDialog();
  CComboBox* pComboBox = static_cast<CComboBox*>(GetDlgItem(IDC_PENWIDTH_COMBO));
  CString penWidthStr;
  pComboBox->AddString(_T("Pen width 1 pixel"));
  for(int i = 1 ; i <= 5 ; ++i)
  {
    penWidthStr.Format(_T("Pen Width 0.0%d inches"), i);
    pComboBox->AddString(penWidthStr);
  }
  pComboBox->SetCurSel(m_PenWidth); 

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


