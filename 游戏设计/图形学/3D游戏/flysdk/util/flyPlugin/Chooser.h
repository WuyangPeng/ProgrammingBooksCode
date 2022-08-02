#if !defined(AFX_CHOOSER_H__40D36E32_7D66_11D2_9263_000021799871__INCLUDED_)
#define AFX_CHOOSER_H__40D36E32_7D66_11D2_9263_000021799871__INCLUDED_

// chooser.h : declaration of the CDialogChooser class
//             This class keeps track of what dialogs to pop up when.

#define LAST_DLG 3
#define FIRST_CUSTOM_STEP 1
#define LAST_CUSTOM_STEP 3
#define MAX_CLASSES 64
#define MAX_PARAM 128

class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CFlypluginAppWiz::Next
	//  & CFlypluginAppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

	int m_nCurrDlg;
	CAppWizStepDlg* m_pDlgs[LAST_DLG + 1];
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSER_H__40D36E32_7D66_11D2_9263_000021799871__INCLUDED_)
