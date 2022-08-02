// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 12.16

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(200);			
	vp.set_vres(200);
	vp.set_pixel_size(1);
	vp.set_samples(num_samples);				

	tracer_ptr = new RayCast(this);	
	background_color = RGBColor(0.0, 0.2, 0.4);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.567);
	set_ambient_light(ambient_ptr);
			
	float fov = 200;
	
	FishEye* left_fisheye_ptr = new FishEye;
	left_fisheye_ptr->set_fov(fov);
	
	FishEye* right_fisheye_ptr = new FishEye;
	right_fisheye_ptr->set_fov(fov);
	
	StereoCamera* stereo_ptr = new StereoCamera; 
	stereo_ptr->set_left_camera(left_fisheye_ptr);
	stereo_ptr->set_right_camera(right_fisheye_ptr);
	stereo_ptr->use_parallel_viewing();
// 	stereo_ptr->use_transverse_viewing();
	stereo_ptr->set_eye(-150, 1000, -500);
	stereo_ptr->set_lookat(-160, 300, -550);  
	stereo_ptr->compute_uvw();
	stereo_ptr->set_stereo_angle(5);  
	stereo_ptr->setup_cameras(); 	
	set_camera(stereo_ptr);	
		
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(1500, 750, 250);
	light_ptr2->scale_radiance(4.5);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	
	// box materials
		
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_cd(0, 0.5, 0.5);     // cyan
	matte_ptr1->set_ka(0.8); 
	matte_ptr1->set_kd(0.3); 
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_cd(1, 0, 0);     	  // red
	matte_ptr2->set_ka(0.8); 
	matte_ptr2->set_kd(0.3);  
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_cd(1, 1, 0);     	// yellow
	matte_ptr3->set_ka(0.8); 
	matte_ptr3->set_kd(0.3); 
	
			
	Grid* grid_ptr = new Grid;
	
	// first row
	
	int num_boxes = 11;
	float wx = 50;
	float wz = 50;
	float h = 500;
	float s = 100;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx, 0, -(j + 1) * wz - j * s), 
								Point3D(0, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr1);
	//	add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// second row
	
	h = 600;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx -wx - s, 0, -(j + 1) * wz - j * s), 
								Point3D(-wx - s, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr2);
//		add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// third row
	
	h = 750; 
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx - 2 * wx - 2 * s, 0, -(j + 1) * wz - j * s), 
								Point3D(-2 * wx - 2 * s, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr3);
//		add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	grid_ptr->setup_cells();
	add_object(grid_ptr);
	
	
	// ground plane with checker
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(6 * wx); 
	checker_ptr->set_color1(0.7);  
	checker_ptr->set_color2(white);
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.20);
	sv_matte_ptr1->set_kd(0.50); 
	sv_matte_ptr1->set_cd(checker_ptr);	
	Plane* plane_ptr = new Plane(Point3D(0, 1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr1);
	add_object(plane_ptr);
}




