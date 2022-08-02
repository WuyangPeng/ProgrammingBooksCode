// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 24.20(a)

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);  
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(12);
		
	tracer_ptr = new Whitted(this);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);	
					
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-35, 25, 35);  
	pinhole_ptr->set_lookat(0.0, 0.4, -0.2);  
	pinhole_ptr->set_view_distance(5500.0);
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(0, 20, 20);     
	light_ptr->scale_radiance(5.0); 
	light_ptr->set_shadows(false);
	add_light(light_ptr);	
	
	
	// the four spheres
		
	float ka = 0.75;
	float kd = 0.75;
	float ks = 0.1;
	float e = 20.0;
	float kr = 1.0;
	
	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(ka); 
	reflective_ptr1->set_kd(kd); 
	reflective_ptr1->set_ks(ks);  
	reflective_ptr1->set_cd(0.168, 0.171, 0.009);    	// pink
	reflective_ptr1->set_exp(e);
	reflective_ptr1->set_kr(kr);
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 1.414, 0.0), 0.866);
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);
	
	
	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(ka); 
	reflective_ptr2->set_kd(kd); 
	reflective_ptr2->set_cd(0.094, 0.243, 0.029);   	// green
	reflective_ptr2->set_ks(ks);    
	reflective_ptr2->set_exp(e);
	reflective_ptr2->set_kr(kr);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(0.0, 0.0, 1.0), 0.866);
	sphere_ptr2->set_material(reflective_ptr2);
	add_object(sphere_ptr2);
	
	
	Reflective* reflective_ptr3 = new Reflective;
	reflective_ptr3->set_ka(ka); 
	reflective_ptr3->set_kd(kd);
	reflective_ptr3->set_cd(0.243, 0.018, 0.164);     	// red 
	reflective_ptr3->set_ks(ks);    
	reflective_ptr3->set_exp(e);
	reflective_ptr3->set_kr(kr);
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(0.866, 0.0, -0.5), 0.866);
	sphere_ptr3->set_material(reflective_ptr3);
	add_object(sphere_ptr3);
	
	
	Reflective* reflective_ptr4 = new Reflective;
	reflective_ptr4->set_ka(ka); 
	reflective_ptr4->set_kd(kd); 
	reflective_ptr4->set_cd(0.094, 0.1, 0.243);    		// blue
	reflective_ptr4->set_ks(ks);    
	reflective_ptr4->set_exp(e);
	reflective_ptr4->set_kr(kr);
	
	Sphere* sphere_ptr4 = new Sphere(Point3D(-0.866, 0.0, -0.5), 0.866);
	sphere_ptr4->set_material(reflective_ptr4);
	add_object(sphere_ptr4);
}


