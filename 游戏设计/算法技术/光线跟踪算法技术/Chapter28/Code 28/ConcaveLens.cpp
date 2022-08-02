// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class ConcaveLens

#include <math.h>

#include "Constants.h"
#include "ConcaveLens.h"
#include "ConcavePartSphere.h"
#include "ConvexOpenCylinder.h"

// ------------------------------------------------------------------------------ constructor

ConcaveLens::ConcaveLens(const double radius, const double _thickness, const double _min_distance)
			: 	Compound(),
				lens_radius(radius),
				thickness(_thickness),
				min_distance(_min_distance)
{
	Point3D center;
	double theta_min, theta_max;
	
	double phi_min = 0.0;
	double phi_max = 360.0;
		
	// top concave part sphere

	double d = (thickness - min_distance) / 2.0;
	double sphere_radius = (d * d + lens_radius * lens_radius) / (2.0 * d);
	
	center = Point3D(0.0, sphere_radius + min_distance/ 2.0, 0.0);
	theta_min = 90.0 + acos(lens_radius / sphere_radius) * 180.0 / PI;  // in degrees 
	theta_max = 180.0;
	objects.push_back(new ConcavePartSphere(center, sphere_radius, phi_min, phi_max, theta_min, theta_max)); 
	
	// bottom concave part sphere
	
	center = Point3D(0.0, -(sphere_radius + min_distance / 2.0), 0.0);
	theta_min = 0.0;
	theta_max = 90.0 - acos(lens_radius / sphere_radius) * 180.0 / PI;  // in degrees 
	objects.push_back(new ConcavePartSphere(center, sphere_radius, phi_min, phi_max, theta_min, theta_max));
		
	// outer surface
	
	objects.push_back(new ConvexOpenCylinder(-thickness / 2.0, thickness / 2.0, lens_radius)); 
	
	// bounding box
	
	bbox.x0 = -lens_radius;
	bbox.x1 = lens_radius;
	bbox.y0 = -thickness / 2.0;
	bbox.y1 = thickness / 2.0; 
	bbox.z0 = -lens_radius;
	bbox.z1 = lens_radius; 		
}
																																																														

// ------------------------------------------------------------------------------ copy constructor

ConcaveLens::ConcaveLens(const ConcaveLens& cc)  			
	: 	Compound(cc),
		lens_radius(cc.lens_radius),
		thickness(cc.thickness),
		min_distance(cc.min_distance)   
{}


// ------------------------------------------------------------------------------ assignment operator

ConcaveLens& 
ConcaveLens::operator= (const ConcaveLens& rhs) {
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs);
	
	lens_radius 	= rhs.lens_radius;
	thickness 		= rhs.thickness;
	min_distance 	= rhs.min_distance;  

	return (*this) ;
}


// ------------------------------------------------------------------------------ destructor
 
ConcaveLens::~ConcaveLens(void) {}


// ------------------------------------------------------------------------------ clone

ConcaveLens* 
ConcaveLens::clone(void) const {
	return (new ConcaveLens(*this));
}	


// ------------------------------------------------------------------------------ get_bounding_box

BBox
ConcaveLens::get_bounding_box(void) {
	return (bbox);
}	


// ------------------------------------------------------------------------------ hit

bool 															 
ConcaveLens::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}																		


