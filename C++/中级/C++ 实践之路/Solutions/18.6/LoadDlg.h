#if !defined (LOADDLG_H)
#define LOADDLG_H
// Bartosz Milewski (c) 2000
#include "Dialog.h"
#include "ListBox.h"

class LoadCtrl : public Dialog::ModalController
{
public:
	LoadCtrl ()
	{
		_path.resize (MAX_PATH + 1);
		ResetBuf ();
	}
	void OnInitDialog () throw (Win::Exception);
    bool OnCommand (int ctrlId, int notifyCode) throw (Win::Exception);

	std::string const & GetPath ()
	{
		return _path;
	}
private:
	void ChangeDirectory ();
	char * GetBuffer () { return &_path [0]; }
	void ResetBuf () { _path [0] = '\0'; }
	int GetBufLen () const { return _path.size (); }
	void SetPath (std::string const & str)
	{
		_path = str;
	}
private:
	std::string 	_path;

	Win::ListBox	_listBox;
};

#endif
