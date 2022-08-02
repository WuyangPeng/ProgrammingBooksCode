// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 14.15
// Instances are discussed in Section 21.4
// Beveled cylinders are discussed in Section 21.5

void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(650);	  		
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 100);
	pinhole_ptr->set_lookat(0, 0, 0);
	pinhole_ptr->set_view_distance(6000); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(20, 0, 20);
	light_ptr2->scale_radiance(3.0);
	add_light(light_ptr2);
	
	// beveled cylinder
	
	float bottom 		= -2.0;
	float top 			= 2.0;
	float radius 		= 1.0;
	float bevel_radius 	= 0.2;
	
	BeveledCylinder* cylinder_ptr1 = new BeveledCylinder(bottom, top, radius, bevel_radius);
	
	for (int j = 0; j < 4; j++) {
	
		Matte* matte_ptr = new Matte;
		matte_ptr->set_ka(0.25); 					
		matte_ptr->set_kd(0.1 + 0.3 * j);
		matte_ptr->set_cd(0.5);
	
		Instance* cylinder_ptr2 = new Instance(cylinder_ptr1);
		cylinder_ptr2->translate(-3.75 + 2.5 * j, 0, 0);
		cylinder_ptr2->set_material(matte_ptr);
		add_object(cylinder_ptr2);
	}
}

