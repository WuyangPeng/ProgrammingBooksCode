#ifndef __CUT_FACE__
#define __CUT_FACE__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// A CutFace is a square in the (x, z) plane with a circular hole in the middle

#include "GeometricObject.h"

//-------------------------------------------------------------------------------- class CutFace

class CutFace: public GeometricObject {

	public:
		
		CutFace(void);   					
		
		CutFace(double _size, double _radius);  
		
		virtual CutFace* 							
		clone(void) const;
	
		CutFace(const CutFace& cf); 

		virtual										
		~CutFace (void);   									

		CutFace& 										
		operator= (const CutFace& rhs);
		
		void
		set_size(const double _size);	
		
		void
		set_radius(const double _radius);						
		
		virtual bool 															 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
	private:
			
		double	size;		// x and w dimensions of the square
		double	radius;		// radius of the hole
};


// inlined access functions

// ------------------------------------------------------------ set_size

inline void
CutFace::set_size(const double _size) {
	size = _size;
}	

		
// ------------------------------------------------------------ set_radius

inline void
CutFace::set_radius(const double _radius) {
	radius = _radius;
}	
#endif
