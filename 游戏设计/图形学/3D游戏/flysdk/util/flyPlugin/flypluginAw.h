#if !defined(AFX_FLYPLUGINAW_H__40D36E27_7D66_11D2_9263_000021799871__INCLUDED_)
#define AFX_FLYPLUGINAW_H__40D36E27_7D66_11D2_9263_000021799871__INCLUDED_

// flypluginaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see flyplugin.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CFlypluginAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);

	CDialogChooser* m_pChooser;
};

// This declares the one instance of the CFlypluginAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global Flypluginaw.  (Its definition is in flypluginaw.cpp.)
extern CFlypluginAppWiz Flypluginaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLYPLUGINAW_H__40D36E27_7D66_11D2_9263_000021799871__INCLUDED_)
