// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 24.40(b).

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_max_depth(1); 
	vp.set_pixel_size(0.0073);
	vp.set_samples(num_samples);
	
	background_color = white;
	
	tracer_ptr = new Whitted(this);
	
	Orthographic* orthographic_ptr = new Orthographic;
	orthographic_ptr->set_eye(0.0, 0.866, 100.0);    
	orthographic_ptr->set_lookat(0.0, 0.866, 0.0);  
	orthographic_ptr->compute_uvw();     
	set_camera(orthographic_ptr);

	
	float kr = 1.0;
	
	// top sphere 
	
	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.0); 
	reflective_ptr1->set_kd(0.0); 
	reflective_ptr1->set_cd(black);
	reflective_ptr1->set_ks(0.0);
	reflective_ptr1->set_exp(1.0);			
	reflective_ptr1->set_kr(kr);
	reflective_ptr1->set_cr(1, 0, 0);  // red
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 1.732, 0.0), 1.0);
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);
	
	// left bottom sphere 
	
	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(0.0); 
	reflective_ptr2->set_kd(0.0); 
	reflective_ptr2->set_cd(black);
	reflective_ptr2->set_ks(0.0);
	reflective_ptr2->set_exp(1.0);				
	reflective_ptr2->set_kr(kr);
	reflective_ptr2->set_cr(0, 1, 0);  // green
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(-1.0, 0.0, 0.0), 1.0);
	sphere_ptr2->set_material(reflective_ptr2);
	add_object(sphere_ptr2);
	
	// right bottom sphere 
	
	Reflective* reflective_ptr3 = new Reflective;
	reflective_ptr3->set_ka(0.0); 
	reflective_ptr3->set_kd(0.0); 
	reflective_ptr3->set_cd(black);
	reflective_ptr3->set_ks(0.0);
	reflective_ptr3->set_exp(1.0);			
	reflective_ptr3->set_kr(kr);
	reflective_ptr3->set_cr(0, 0, 1);  // blue
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(1.0, 0.0, 0.0), 1.0);
	sphere_ptr3->set_material(reflective_ptr3);
	add_object(sphere_ptr3);
}	
	
	
