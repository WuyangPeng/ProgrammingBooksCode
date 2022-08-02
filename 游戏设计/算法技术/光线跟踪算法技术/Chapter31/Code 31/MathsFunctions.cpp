// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// The following functions are required for the noise classes and the Wood class.

// clamp, mod, mix_color, and smooth_step are RenderMan Shading Language functions
// They are discussed in Peachey in Ebert et al. (2003), where the RenderMan name for mix_color is mix.

// smooth_pulse and smooth_pulse_train are discussed in Apodaca and Gritz (2000). 


// Add the following prototypes to the Maths.h file.

double
mod(double a, const double b); 

double 
smooth_pulse(double e0, double e1, double e2, double e3, double x);

double 
smooth_pulse_train(double e0, double e1, double e2, double e3, double period, double x);

double
smooth_step(double a, double b, double x);

RGBColor
mix_color(const RGBColor& c0, const RGBColor& c1, const double f);

double
mix_double(const double a, const double b, const double f);

double
clamp(const double x, const double min, const double max);



// Add the following inlined function definition to the Maths.h file.

// -------------------------------------------------------------------------- clamp

inline double
clamp(const double x, const double min, const double max) {
	return (x < min ? min : (x > max ? max : x));
}



// Add the following function definitions to the Maths.cpp file.

// -------------------------------------------------------------------------- mod

double
mod(double a, const double b) {
	int n = (int) (a / b);
	
	a -= n * b;
	if (a < 0.0)
		a += b;
	
	return (a);
}


// -------------------------------------------------------------------------- smooth_pulse

double 
smooth_pulse(double e0, double e1, double e2, double e3, double x) {
	return (smooth_step (e0, e1, x) - smooth_step (e2, e3, x));
}


// -------------------------------------------------------------------------- smooth_pulse_train
// calls smooth_pulse and mod

double 
smooth_pulse_train(double e0, double e1, double e2, double e3, double period, double x) {
	return (smooth_pulse(e0, e1, e2, e3, mod(x, period)));
}


// -------------------------------------------------------------------------- smooth_step

double
smooth_step(double a, double b, double x) {
	if (x < a)
		return (0.0);
	
	if (x >= b)
		return (1.0);
		
	double y = (x - a) / ( b - a);  // normalise to [0, 1]
	
	return (y * y * (3.0 - 2.0 * y));
}


// -------------------------------------------------------------------------- mix_color

RGBColor
mix_color(const RGBColor& c0, const RGBColor& c1, const double f) {
	return ((1.0 - f) * c0 + f * c1);
}


// -------------------------------------------------------------------------- mix_double

double
mix_double(const double a, const double b, const double f) {
	return ((1.0 - f) * a + f * b);
}



