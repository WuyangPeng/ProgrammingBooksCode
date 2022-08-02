# include "calling.h"

volatile int z;

int C::f1(int arg)	{ x_ = arg; return arg; }

int C::f0()			{ return x_; }
