// ScaleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "ScaleDialog.h"


// CScaleDialog dialog

IMPLEMENT_DYNAMIC(CScaleDialog, CDialog)

CScaleDialog::CScaleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CScaleDialog::IDD, pParent)
  , m_Scale(1)
{

}

CScaleDialog::~CScaleDialog()
{
}

void CScaleDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScaleDialog, CDialog)
  ON_BN_CLICKED(IDC_SCALE1, &CScaleDialog::OnBnClickedScale1)
  ON_BN_CLICKED(IDC_SCALE2, &CScaleDialog::OnBnClickedScale2)
  ON_BN_CLICKED(IDC_SCALE3, &CScaleDialog::OnBnClickedScale3)
  ON_BN_CLICKED(IDC_SCALE4, &CScaleDialog::OnBnClickedScale4)
  ON_BN_CLICKED(IDC_SCALE5, &CScaleDialog::OnBnClickedScale5)
  ON_BN_CLICKED(IDC_SCALE6, &CScaleDialog::OnBnClickedScale6)
  ON_BN_CLICKED(IDC_SCALE7, &CScaleDialog::OnBnClickedScale7)
  ON_BN_CLICKED(IDC_SCALE8, &CScaleDialog::OnBnClickedScale8)
END_MESSAGE_MAP()


// CScaleDialog message handlers


BOOL CScaleDialog::OnInitDialog()
{
  CDialog::OnInitDialog();
  switch(m_Scale)
  {
  case 1:
    CheckDlgButton(IDC_SCALE1, 1);
    break;
  case 2:
    CheckDlgButton(IDC_SCALE2, 1);
    break;
  case 3:
    CheckDlgButton(IDC_SCALE3, 1);
    break;
  case 4:
    CheckDlgButton(IDC_SCALE4, 1);
    break;
  case 5:
    CheckDlgButton(IDC_SCALE5, 1);
    break;
  case 6:
    CheckDlgButton(IDC_SCALE6, 1);
    break;
  case 7:
    CheckDlgButton(IDC_SCALE7, 1);
    break;
  case 8:
    CheckDlgButton(IDC_SCALE8, 1);
    break;
  default:
    CheckDlgButton(IDC_SCALE1, 1);
    break;
  }


  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


void CScaleDialog::OnBnClickedScale1()
{
  m_Scale = 1;
}


void CScaleDialog::OnBnClickedScale2()
{
  m_Scale = 2;
}


void CScaleDialog::OnBnClickedScale3()
{
  m_Scale = 3;
}


void CScaleDialog::OnBnClickedScale4()
{
  m_Scale = 4;
}


void CScaleDialog::OnBnClickedScale5()
{
  m_Scale = 5;
}


void CScaleDialog::OnBnClickedScale6()
{
  m_Scale = 6;
}


void CScaleDialog::OnBnClickedScale7()
{
  m_Scale = 7;
}


void CScaleDialog::OnBnClickedScale8()
{
  m_Scale = 8;
}
