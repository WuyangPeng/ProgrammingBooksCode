#pragma once
#include "afxcmn.h"


// CScaleDialog dialog

class CScaleDialog : public CDialog
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScaleDialog();

// Dialog Data
	enum { IDD = IDD_SCALE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  // Stores the current view scale
  int m_Scale;
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedScale1();
  afx_msg void OnBnClickedScale2();
  afx_msg void OnBnClickedScale3();
  afx_msg void OnBnClickedScale4();
  afx_msg void OnBnClickedScale5();
  afx_msg void OnBnClickedScale6();
  afx_msg void OnBnClickedScale7();
  afx_msg void OnBnClickedScale8();
};
