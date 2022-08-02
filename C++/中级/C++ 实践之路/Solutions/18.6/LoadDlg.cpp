#include "LoadDlg.h"
// Bartosz Milewski (c) 2000
#include "Resource.h"

void LoadCtrl::OnInitDialog () throw (Win::Exception)
{
	_listBox.Init (GetWindow (), IDC_LIST);
	_listBox.ListDirectory (GetWindow (), GetBuffer (), IDC_STATICPATH);
}

void LoadCtrl::ChangeDirectory ()
{
	::SetCurrentDirectory (GetBuffer ());
	ResetBuf ();
	_listBox.ListDirectory (GetWindow (), GetBuffer (), IDC_STATICPATH);
}

bool LoadCtrl::OnCommand (int ctrlId, int notifyCode) throw (Win::Exception)
{
	if (ctrlId == IDOK || ctrlId == IDC_LIST && notifyCode == LBN_DBLCLK)
	{
		if (_listBox.GetSelectedPath (GetWindow (), GetBuffer (), GetBufLen ()))
		{
			// directory selected
			ChangeDirectory ();
		}
		else if (_listBox.IsSelection ())
			EndOk ();
		else
			EndCancel ();
		return true;
	}
	else if (ctrlId == IDCANCEL)
	{
		EndCancel ();
		return true;
	}
	return false;
}
