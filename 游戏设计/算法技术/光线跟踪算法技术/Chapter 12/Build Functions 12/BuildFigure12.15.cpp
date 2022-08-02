// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 12.15

void 												
World::build(void)
{
	int num_samples = 16;
	
	vp.set_hres(200);                                                               	  		
	vp.set_vres(150);
	vp.set_pixel_size(0.2);  
	vp.set_samples(num_samples);
	vp.set_max_depth(1);
	
	tracer_ptr = new RayCast(this);
	background_color = white;
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	float vpd = 98;
	float focal_distance = 74;
	float lens_radius = 1.0;
	
	ThinLens* left_camera_ptr = new ThinLens;
	left_camera_ptr->set_sampler(new MultiJittered(num_samples));	
	left_camera_ptr->set_view_distance(vpd);  
	left_camera_ptr->set_focal_distance(focal_distance); 
	left_camera_ptr->set_lens_radius(lens_radius);

	ThinLens* right_camera_ptr = new ThinLens;
	right_camera_ptr->set_sampler(new MultiJittered(num_samples));	
	right_camera_ptr->set_view_distance(vpd);   
	right_camera_ptr->set_focal_distance(focal_distance); 
	right_camera_ptr->set_lens_radius(lens_radius);

	StereoCamera* stereo_ptr = new StereoCamera(left_camera_ptr, right_camera_ptr);
	stereo_ptr->use_parallel_viewing();
//	stereo_ptr->use_transverse_viewing();
	stereo_ptr->set_pixel_gap(5);
	stereo_ptr->set_eye(0, 6, 50);
	stereo_ptr->set_lookat(0, 6, 0);
	stereo_ptr->compute_uvw();
	stereo_ptr->set_stereo_angle(2.0);  // in degrees
	stereo_ptr->setup_cameras(); 
	set_camera(stereo_ptr);

	
	// Directional light 

	Directional* light_ptr = new Directional;
	light_ptr->set_direction(1, 1, 1);     
	light_ptr->scale_radiance(7.5); 
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// box 1
	
	Checker3D* checker_ptr1 = new Checker3D;
	checker_ptr1->set_size(2.0);
	checker_ptr1->set_color1(1, 1, 0.33);  		// lemon
	checker_ptr1->set_color2(black);	 
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.5);
	sv_matte_ptr1->set_kd(0.35);
	sv_matte_ptr1->set_cd(checker_ptr1);
	
	Box* box_ptr1 = new Box(Point3D(-9, 0, -1), Point3D(-3, 12, 0));
	box_ptr1->set_material(sv_matte_ptr1);
	add_object(box_ptr1);
		
	
	// box 2
	
	Checker3D* checker_ptr2 = new Checker3D;
	checker_ptr2->set_size(2.0);
	checker_ptr2->set_color1(black);  	
	checker_ptr2->set_color2(0.1, 1, 0.5);	  	// green
	
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.5);
	sv_matte_ptr2->set_kd(0.35);
	sv_matte_ptr2->set_cd(checker_ptr2);	
	
	Box* box_ptr2 = new Box(Point3D(-3.25, 0, -25), Point3D(4.75, 14, -24));
	box_ptr2->set_material(sv_matte_ptr2);
	add_object(box_ptr2);
	
	
	// box 3
	
	Checker3D* checker_ptr3 = new Checker3D;
	checker_ptr3->set_size(2.0);
	checker_ptr3->set_color1(black);  	
	checker_ptr3->set_color2(1, 0.6, 0.15);	  	// orange
	
	SV_Matte* sv_matte_ptr3 = new SV_Matte;		
	sv_matte_ptr3->set_ka(0.5);
	sv_matte_ptr3->set_kd(0.35);
	sv_matte_ptr3->set_cd(checker_ptr3);
		
	Box* box_ptr3 = new Box(Point3D(8, 0, -49), Point3D(18, 15, -48));
	box_ptr3->set_material(sv_matte_ptr3);
	add_object(box_ptr3);
	

	// ground plane
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(8.0);
	checker_ptr->set_color1(0.25);  			// gray
	checker_ptr->set_color2(white);	 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.35);
	sv_matte_ptr->set_cd(checker_ptr);	

	Plane* plane_ptr1 = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr1->set_material(sv_matte_ptr);
	add_object(plane_ptr1);
}



