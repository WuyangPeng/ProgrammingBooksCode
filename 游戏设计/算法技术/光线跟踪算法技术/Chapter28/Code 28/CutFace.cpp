// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "CutFace.h"

// ----------------------------------------------------------------  default constructor

CutFace::CutFace(void)
	: 	size(1.0),
		radius(0.5)				
{}


// ----------------------------------------------------------------  constructor


CutFace::CutFace(double _size, double _radius)
	: 	size(_size),
		radius(_radius)
{}




// ---------------------------------------------------------------- clone

CutFace* 
CutFace::clone(void) const {
	return(new CutFace (*this));
}


// ---------------------------------------------------------------- copy constructor

CutFace::CutFace(const CutFace& cf)
	:	size(cf.size),
		radius(cf.radius)			
{}



// ---------------------------------------------------------------- assignment operator

CutFace& 
CutFace::operator= (const CutFace& rhs) {
	if (this == &rhs)
		return (*this);
	
	size 	= rhs.size;
	radius 	= rhs.radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

CutFace::~CutFace(void) {}



// ------------------------------------------------------------------------------ hit

bool 															 
CutFace::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	double t = -ray.o.y / ray.d.y;            
														
	if (t > kEpsilon) {
		double xi = ray.o.x + t * ray.d.x; 
		double zi = ray.o.z + t * ray.d.z;
		double d = xi * xi + zi * zi;
		double size_on_two = 0.5 * size;
				
		if ((-size_on_two <= xi && xi <= size_on_two) && (-size_on_two <= zi && zi <= size_on_two)  // inside square
				&& 	d >= radius * radius)															// outside circle
		{	
			tmin 				= t;
			sr.normal 			= Normal(0.0, 1.0, 0.0);
			sr.local_hit_point 	= ray.o + t * ray.d;
			
			return (true);
		}	
		else
			return (false);
	}
	
	return (false);
}







