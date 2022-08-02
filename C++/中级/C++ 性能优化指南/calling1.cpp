# include "calling.h"

int C1::f1(int arg)	{ int x = c_.f1(arg); return x+1; }

int C1::f0()		{ int x = c_.f0(); return x-1; }
