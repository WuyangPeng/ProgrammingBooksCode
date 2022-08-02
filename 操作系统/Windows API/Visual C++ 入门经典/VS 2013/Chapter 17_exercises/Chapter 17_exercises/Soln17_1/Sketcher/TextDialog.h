#pragma once


// CTextDialog dialog

class CTextDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDialog)

public:
	CTextDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTextDialog();

// Dialog Data
	enum { IDD = IDD_TEXT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  // Stores the text entered in the edit box
  CString m_TextString;
};
