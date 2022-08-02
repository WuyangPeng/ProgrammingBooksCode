// chooser.cpp : Implements the CDialogChooser class
//

#include "stdafx.h"
#include "flyplugin.h"

#include "chooser.h"
#include "cstm1dlg.h"
#include "cstm2dlg.h"
#include "cstm3dlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDialogChooser::CDialogChooser()
{
	m_pDlgs[0] = NULL;

	m_pDlgs[1] = new CCustom1Dlg;
	m_pDlgs[2] = new CCustom2Dlg;
	m_pDlgs[3] = new CCustom3Dlg;

	m_nCurrDlg = 0;
}
CDialogChooser::~CDialogChooser()
{
	for (int i = FIRST_CUSTOM_STEP; i <= LAST_CUSTOM_STEP; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}
}

CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(0 <= m_nCurrDlg && m_nCurrDlg < LAST_DLG);
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);

	m_nCurrDlg++;
	return m_pDlgs[m_nCurrDlg];
}

CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
	ASSERT(1 <= m_nCurrDlg && m_nCurrDlg <= LAST_DLG);
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);

	m_nCurrDlg--;
	return m_pDlgs[m_nCurrDlg];
}
