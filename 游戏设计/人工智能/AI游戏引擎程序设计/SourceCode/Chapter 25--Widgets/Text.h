#pragma once
#include "afxwin.h"
#include "Widgets/Widget.h"

/********************************************************************
*	Text:			Text widgets don't actually DO anything, but
*					they are useful for labeling widgets or sections
*					of widgets.
*
*******************************************************************/
class Text : public Widget
{
public:
	Text(void);
	~Text(void);
	int Draw( int pos );
	CStatic m_text;
};
