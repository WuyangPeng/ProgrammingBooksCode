// TextDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "TextDialog.h"
#include "afxdialogex.h"


// CTextDialog dialog

IMPLEMENT_DYNAMIC(CTextDialog, CDialogEx)

CTextDialog::CTextDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextDialog::IDD, pParent)
  , m_TextString(_T(""))
{

}

CTextDialog::~CTextDialog()
{
}

void CTextDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT_TEXT, m_TextString);
	DDV_MaxChars(pDX, m_TextString, 100);
}


BEGIN_MESSAGE_MAP(CTextDialog, CDialogEx)
END_MESSAGE_MAP()


// CTextDialog message handlers
