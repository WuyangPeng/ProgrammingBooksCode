#if !defined (SAVEDLG_H)
#define SAVEDLG_H
// Bartosz Milewski (c) 2000
#include "Dialog.h"
#include "Edit.h"

class SaveCtrl : public Dialog::ModalController
{
public:
	void OnInitDialog () throw (Win::Exception);
    bool OnCommand (int ctrlId, int notifyCode) throw (Win::Exception);
	std::string const & GetPath ()
	{
		return _path;
	}
private:
	void SetPath (std::string const & str)
	{
		_path = str;
	}
	std::string _path;

	Win::Edit	_edit;
};

#endif
