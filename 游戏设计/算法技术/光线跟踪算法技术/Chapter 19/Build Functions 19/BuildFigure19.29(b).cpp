// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 19.29(b)

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 3.25, 5);
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->set_view_distance(900); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
		
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(20, 15, 15);
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(false);
	add_light(light_ptr1);

	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.3);    
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(1, 1, 0.25);  	// lemon
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.4);    
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(0.5);   			// gray
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.4);    
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(0.25, 1, 1); 	// cyan
	
	// ring parameters	
		
	float y0 = -0.25;
	float y1 = 0.25;
	float inner_radius = 0.5;
	float outer_radius = 1.0;
	
	ThickRing* ring_ptr = new ThickRing(y0, y1, inner_radius, outer_radius); 
	ring_ptr->set_bottom_material(matte_ptr1);		// lemon
	ring_ptr->set_top_material(matte_ptr1);			// lemon
	ring_ptr->set_inner_wall_material(matte_ptr2);	// gray
	ring_ptr->set_outer_wall_material(matte_ptr3);	// cyan
	add_object(ring_ptr);
}

