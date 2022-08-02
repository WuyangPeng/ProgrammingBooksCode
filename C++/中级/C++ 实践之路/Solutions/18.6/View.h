#if !defined (VIEW_H)
#define VIEW_H
// Bartosz Milewski (c) 2000
#include "StatusBar.h"
#include "ListBox.h"
#include "Edit.h"

class Calculator;

class EditController: public Win::SubController
{
public:
	bool OnKeyDown (int vKey, int flags) throw ();
};

class View
{
public:
	View (Win::Dow winTop, Calculator & calc);
	void Size (int width, int height);
	void SetFocus ()
	{
		_edit.SetFocus ();
	}
	std::string GetInput ()
	{
		return _edit.GetText ();
	}
	void SetResult (char const * str);
	void UpdateMemory ();
	void UpdateHistory (std::string const & str, double result);
private:
	std::string FormatMemoryString (int id);
private:
	Calculator	  & _calc;	// source of data
	
	int _charWidth, _charHeight;
	int _wValue;		// width in pixels of value field
	int _varNameChars;  // width in chars of name field
	
	EditController	_editCtrl;

	Win::StatusBar	_status;
	Win::ListBox	_historyView;
	Win::ListBox	_memoryView;
	Win::Edit		_edit;
	Win::Edit		_result;
};

#endif
