#pragma once
#include "stdafx.h"

/********************************************************************
*	Widget:		Widget is the base class for all widget types. If
*				you decide to make your own new kinds of widgets, you
*				must base it on this class, and override Draw. You 
*				should otherwise never need to explicitly create or
*				deal with the Widget class.
*
*******************************************************************/
class Widget : public CWnd {
public:
	virtual void Update();
	virtual int Draw( int pos )=0;
};