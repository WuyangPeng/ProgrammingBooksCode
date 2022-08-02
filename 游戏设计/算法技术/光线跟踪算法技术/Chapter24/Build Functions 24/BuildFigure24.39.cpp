// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 24.39

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(10);
	
	tracer_ptr = new Whitted(this);	

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.0);
	set_ambient_light(ambient_ptr);	
		
			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 0); 
	pinhole_ptr->set_lookat(0, 0, -100);
	pinhole_ptr->set_view_distance(500);
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_ce(1.0, 1.0, 0.5); 	// yellow 
	emissive_ptr->scale_radiance(0.85);  


	ConcaveSphere* sphere_ptr = new ConcaveSphere;
	sphere_ptr->set_radius(1000000.0);
	sphere_ptr->set_material(emissive_ptr);
	sphere_ptr->set_shadows(false);
	add_object(sphere_ptr);

	
	// cylinder
	
	Reflective* reflective_ptr = new Reflective;			
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.0); 
	reflective_ptr->set_cd(black);
	reflective_ptr->set_ks(0.0);
	reflective_ptr->set_exp(1.0);
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(1.0, 0.75, 0.5);  // orange
	
	
	double bottom 	= -2.0;
	double top 		= 2.0; 
	double radius	= 10.0;
	
	OpenCylinder* cylinder_ptr2 = new OpenCylinder(bottom, top, radius);
	cylinder_ptr2->set_material(reflective_ptr);
	add_object(cylinder_ptr2);
}


