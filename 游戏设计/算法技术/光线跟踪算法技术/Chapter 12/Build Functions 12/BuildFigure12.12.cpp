// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 12.12

void 												
World::build(void) {
	int num_samples = 1;

	vp.set_hres(200);	
	vp.set_vres(200);
	vp.set_pixel_size(0.05);		
	vp.set_samples(num_samples);	
	
	tracer_ptr = new RayCast(this);			

	float vpd = 100;  // view plane distance for 200 x 200 pixel images

	Pinhole* left_camera_ptr = new Pinhole;  
	left_camera_ptr->set_view_distance(vpd);
	
	Pinhole* right_camera_ptr = new Pinhole; 
	right_camera_ptr->set_view_distance(vpd);
	
	StereoCamera* stereo_ptr = new StereoCamera;		
	stereo_ptr->set_left_camera(left_camera_ptr);
	stereo_ptr->set_right_camera(right_camera_ptr);
	stereo_ptr->use_parallel_viewing();
//	stereo_ptr->use_transverse_viewing();
	stereo_ptr->set_pixel_gap(5);       // in pixels
	stereo_ptr->set_eye(5, 0, 100);
	stereo_ptr->set_lookat(0);
	stereo_ptr->compute_uvw();
	stereo_ptr->set_stereo_angle(0.75);  // in degrees
	stereo_ptr->setup_cameras(); 
	set_camera(stereo_ptr);
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(100, 100, 100);
	light_ptr->scale_radiance(3);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// sphere materials
	
	Phong* phong_ptr1 = new Phong;			
	phong_ptr1->set_cd(0, 0.5, 0.5);   	// cyan
	phong_ptr1->set_ka(0.4); 
	phong_ptr1->set_kd(0.6);
	phong_ptr1->set_ks(0.2); 
	phong_ptr1->set_exp(20); 
	
	Phong*	phong_ptr2 = new Phong;
	phong_ptr2->set_cd(0.85, 0.6, 0.2); 	// brown				
	phong_ptr2->set_ka(0.3); 
	phong_ptr2->set_kd(0.7);
	phong_ptr2->set_ks(0.08);
	phong_ptr2->set_exp(20);  
	
	Phong*	phong_ptr3 = new Phong;			
	phong_ptr3->set_cd(1, 1, 0);     		// yellow
	phong_ptr3->set_ka(0.2); 
	phong_ptr3->set_kd(0.6);
	phong_ptr3->set_ks(0.08); 
	phong_ptr3->set_exp(20);   
	
	// the spheres
	
	Sphere* sphere1 = new Sphere(Point3D(0, 0, 35), 0.75);
	sphere1->set_material(phong_ptr1);
	add_object(sphere1);
	
	Sphere* sphere2 = new Sphere(Point3D(0), 2);
	sphere2->set_material(phong_ptr2);
	add_object(sphere2);
	
	Sphere* sphere3 = new Sphere(Point3D(1.5, 0, -80), 2);
	sphere3->set_material(phong_ptr3);
	add_object(sphere3);	
}

