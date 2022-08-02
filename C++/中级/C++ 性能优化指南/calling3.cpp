# include "calling.h"

int C3::f1(int arg)	{ int x = c_.f1(arg); return x+3; }

int C3::f0()		{ int x = c_.f0(); return x-3; }
