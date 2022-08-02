# include "calling.h"

int C4::f1(int arg)	{ int x = c_.f1(arg); return x+4; }

int C4::f0()		{ int x = c_.f0(); return x-4; }
