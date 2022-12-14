// PenDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "PenDialog.h"
#include "afxdialogex.h"


// CPenDialog dialog

IMPLEMENT_DYNAMIC(CPenDialog, CDialogEx)

CPenDialog::CPenDialog(CWnd* pParent /*=NULL*/)
: CDialogEx(CPenDialog::IDD, pParent)
, m_PenWidth(0)
{

}

CPenDialog::~CPenDialog()
{
}

void CPenDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_LBIndex(pDX, IDC_PEN_WIDTH_LIST, m_PenWidth);
	DDV_MinMaxInt(pDX, m_PenWidth, 0, 5);
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialogEx)
END_MESSAGE_MAP()


// CPenDialog message handlers


BOOL CPenDialog::OnInitDialog()
{
  CDialogEx::OnInitDialog();
  CListBox* pListBox{ static_cast<CListBox*>(GetDlgItem(IDC_PENWIDTH_LIST)) };
  CString penWidthStr;

  // The first string in the list box is a special case
  penWidthStr.Format(_T("Pen Width 1 pixel"));
  pListBox->AddString(penWidthStr);

  // Now add the remaining strings
  for (int i{ 1 }; i <= 5; ++i)
  {
    penWidthStr.Format(_T("Pen Width 0.0%d inches"), i);
    pListBox->AddString(penWidthStr);
  }
  pListBox->SetCurSel(m_PenWidth);        // Set current scale


  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}