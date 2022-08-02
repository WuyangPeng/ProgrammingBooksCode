// ScaleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "ScaleDialog.h"
#include "afxdialogex.h"


// CScaleDialog dialog

IMPLEMENT_DYNAMIC(CScaleDialog, CDialogEx)

CScaleDialog::CScaleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScaleDialog::IDD, pParent)
  , m_Scale(0)
{

}

CScaleDialog::~CScaleDialog()
{
}

void CScaleDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_SCALE, m_Scale);
  DDV_MinMaxInt(pDX, m_Scale, 1, 8);
  DDX_Control(pDX, IDC_SPIN_SCALE, m_Spin);
}


BEGIN_MESSAGE_MAP(CScaleDialog, CDialogEx)
END_MESSAGE_MAP()


// CScaleDialog message handlers


BOOL CScaleDialog::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  m_Spin.SetRange(1, 8);               // Set the spin control range

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
