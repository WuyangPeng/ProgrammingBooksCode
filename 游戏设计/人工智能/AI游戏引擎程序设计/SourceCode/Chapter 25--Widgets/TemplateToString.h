#pragma once

#include "stdafx.h"

/********************************************************************
*	TemplateToString:	This is a utility class that I use to print
*						the value of an int, unsigned int, or float
*						variable to a CEdit widget. You shouldn't
*						need to mess with this unless you decide
*						to make ScrubberWidgets that can handle
*						other types.
*
*******************************************************************/
template <class __type> class TemplateToString
{
public:
      char * EchoType()              {return EchoTypeHelper(Inst);}
	  char * EchoTypeHelper(int)     {		sprintf( str, "%d", Inst); 
											return str; }
	  char * EchoTypeHelper(unsigned int){	sprintf( str, "%d", Inst);
											return str; }
      char * EchoTypeHelper(float)   {		sprintf(str, "%.3f", Inst); 
											return str; }
	char str[16];
      __type      Inst;
};