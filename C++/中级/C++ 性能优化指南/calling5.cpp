# include "calling.h"

int C5::f1(int arg)	{ int x = c_.f1(arg); return x+5; }

int C5::f0()		{ int x = c_.f0(); return x-5; }
