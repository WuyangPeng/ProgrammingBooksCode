// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for the Chapter 12 page 1 image


void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(300);
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	background_color = RGBColor(0.0, 0.2, 0.4);
	
	// stereo camera setup using fisheye cameras
	
	float fov = 130.0;

	FishEye* left_camera_ptr = new FishEye;
	left_camera_ptr->set_fov(fov);
	
	FishEye* right_camera_ptr = new FishEye;
	right_camera_ptr->set_fov(fov);

	StereoCamera* stereo_ptr = new StereoCamera;	
	stereo_ptr->set_left_camera(left_camera_ptr);
	stereo_ptr->set_right_camera(right_camera_ptr);
//	stereo_ptr->use_parallel_viewing();
	stereo_ptr->use_transverse_viewing();
	stereo_ptr->set_pixel_gap(5);       // in pixels
	stereo_ptr->set_eye(100.0, 750.0, 0.0);
	stereo_ptr->set_lookat(0.0);
	stereo_ptr->compute_uvw();
	stereo_ptr->set_stereo_angle(5.0);  // in degrees
	stereo_ptr->setup_cameras(); 
	set_camera(stereo_ptr);
	
		
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(0, 350, 0);   
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(0, 2000, 0);  
	light_ptr2->scale_radiance(2.0);
	light_ptr2->scale_radiance(1.0);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	
	// cylinder materials
		
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_cd(1, 1, 0);     	// yellow
	matte_ptr1->set_ka(0.4); 
	matte_ptr1->set_kd(0.5); 
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_cd(1, 0.35, 0);     // red
	matte_ptr2->set_ka(0.4); 
	matte_ptr2->set_kd(0.5);  
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_cd(0, 0.5, 0.5);    // cyan
	matte_ptr3->set_ka(0.4); 
	matte_ptr3->set_kd(0.5); 
	
	
	// construct rings of cylinders stored in a grid
		
	Grid* grid_ptr = new Grid;
	
	int num_cylinders = 12;
	float bottom = 0.0;
	float top = 500.0;
	float radius = 25.0;
	float ring_radius = 150.0;
	float delta_phi = 360.0 / num_cylinders;  // in degrees
	
	// inner ring
	
	for (int j = 0; j < num_cylinders; j++) {
		Instance* cylinder_ptr = new Instance (new SolidCylinder(bottom, top, radius));
		cylinder_ptr->set_material(matte_ptr1);
		cylinder_ptr->translate(0, 0, ring_radius);
		cylinder_ptr->rotate_y(j * delta_phi);
		cylinder_ptr->set_bounding_box();
//		add_object(cylinder_ptr);
		grid_ptr->add_object(cylinder_ptr);
	}
		
	
	// middle ring
	
	num_cylinders = 16;
	top = 450.0;
	ring_radius = 350.0;
	delta_phi = 360.0 / num_cylinders;  // in degrees
	
	for (int j = 0; j < num_cylinders; j++) {
		Instance* cylinder_ptr = new Instance (new SolidCylinder(bottom, top, radius));
		cylinder_ptr->set_material(matte_ptr3);
		cylinder_ptr->translate(0, 0, ring_radius);
		cylinder_ptr->rotate_y(j * delta_phi);
		cylinder_ptr->set_bounding_box();
//		add_object(cylinder_ptr);
		grid_ptr->add_object(cylinder_ptr);
	}
	
	
	// outer ring
	
	num_cylinders = 16;
	top = 325.0;
	ring_radius = 500.0;
	delta_phi = 360.0 / num_cylinders;  // in degrees
	
	for (int j = 0; j < num_cylinders; j++) {
		Instance* cylinder_ptr = new Instance (new SolidCylinder(bottom, top, radius));
		cylinder_ptr->set_material(matte_ptr2);
		cylinder_ptr->translate(0, 0, ring_radius);
		cylinder_ptr->rotate_y(j * delta_phi + 10);
		cylinder_ptr->set_bounding_box();
//		add_object(cylinder_ptr);
		grid_ptr->add_object(cylinder_ptr);
	}
	
	grid_ptr->setup_cells();
	add_object(grid_ptr);
	
	
	// ground plane with checkers:
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(200.0); 
	checker_ptr->set_color1(0.5);   
	checker_ptr->set_color2(white);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.20);
	sv_matte_ptr->set_kd(0.50); 
	sv_matte_ptr->set_cd(checker_ptr);	
	Plane* plane_ptr = new Plane(Point3D(0, 1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);
}




