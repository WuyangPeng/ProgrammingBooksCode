// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.9(a)
// There is no separate build function for Figure 21.9(b), as that image is 
// rendered by commenting out parts of the BeveledWedge constructor

void 												
World::build(void) {
	int num_samples = 16;

	vp.set_hres(500);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(50, 40, 30);			
	pinhole_ptr->set_lookat(0.25, 0.25, 0);
	pinhole_ptr->set_view_distance(4000);   
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(20, 30, 30);
	light_ptr2->scale_radiance(2.5);   
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.25);    
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(0.5, 1, 0.5);	  // green
	
	// wedge1 parameters
	
	float y0 = -1.0;		// minimum y value
	float y1 = 2;			// maximum y value
	float r0 = 1.5;			// inner radius
	float r1 = 3;			// outer radius
	float rb = 0.25;		// bevel radius
	float phi0 = 140;		// minimum azimuth angle in degrees
	float phi1 = 350;		// maximum azimuth angle in degrees
	
	BeveledWedge* wedge_ptr1 = new BeveledWedge(y0, y1, r0, r1, rb, phi0, phi1);
	wedge_ptr1->set_material(matte_ptr1);
	add_object(wedge_ptr1);
	
		
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.25);    
	matte_ptr2->set_kd(0.85);
	matte_ptr2->set_cd(1.0, 0.5, 0.0);	// orange
	
	// wedge2 parameters
	
	y0 = -1.5;		// minimum y value
	y1 = 1.25;		// minimum y value
	r0 = 0.5;		// inner radius
	r1 = 4.0;		// outer radius
	rb = 0.075;		// bevel radius
	phi0 = 110;		// minimum azimuth angle in degrees
	phi1 = 130;		// maximum azimuth angle in degrees
		
	BeveledWedge* wedge_ptr2 = new BeveledWedge(y0, y1, r0, r1, rb, phi0, phi1);
	wedge_ptr2->set_material(matte_ptr2);
	add_object(wedge_ptr2);	
		
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_cd(1, 1, 0.0);	// yellow
	matte_ptr3->set_ka(0.25);    
	matte_ptr3->set_kd(0.85);
	
	// wedge3 parameters
	
	y0 = -0.75;		// minimum y value
	y1 = 0.5;		// minimum y value
	r0 = 1.25;		// inner radius
	r1 = 3.75;		// outer radius
	rb = 0.1;		// bevel radius
	phi0 = 0;		// minimum azimuth angle in degrees
	phi1 = 90;		// maximum azimuth angle in degrees
		
	BeveledWedge* wedge_ptr3 = new BeveledWedge(y0, y1, r0, r1, rb, phi0, phi1);
	wedge_ptr3->set_material(matte_ptr3);
	add_object(wedge_ptr3);		
}

