// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds Figure9.10

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);			
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
			
	Pinhole* camera_ptr = new Pinhole;
	
	// for Figure 16.5(a)

	camera_ptr->set_eye(350, 1000, 500);   
	camera_ptr->set_lookat(-175, 550, -40);  
	camera_ptr->set_view_distance(350);
	
/*
	
	// for Figure 16.5(b)
	
	camera_ptr->set_eye(1500, 750, 250);   
	camera_ptr->set_lookat(-50, 300, -600);  
	camera_ptr->set_view_distance(650);
	
*/

	camera_ptr->compute_uvw(); 
	set_camera(camera_ptr);

	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(1500, 750, 250);   
	light_ptr->scale_radiance(4.5);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// box materials
		
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_cd(0, 0.5, 0.5);     // cyan
	matte_ptr1->set_ka(0.4); 
	matte_ptr1->set_kd(0.5); 
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_cd(1, 0, 0);     	  // red
	matte_ptr2->set_ka(0.4); 
	matte_ptr2->set_kd(0.5);  
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_cd(0.5, 0.6, 0);     // green
	matte_ptr3->set_ka(0.4); 
	matte_ptr3->set_kd(0.5); 
	
	
	// Construct rows of boxes stored in a grid
		
	Grid* grid_ptr = new Grid;
	
	// first row
	
	int num_boxes = 11;
	float wx = 50;
	float wz = 50;
	float h = 300;
	float s = 100;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx, 0, -(j + 1) * wz - j * s), 
								Point3D(0, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr1);
	//	add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// second row
	
	h = 450;
	
	for (int j = 0; j <= num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx -wx - s, 0, -(j + 1) * wz - j * s), 
								Point3D(-wx - s, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr2);
//		add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// third row
	
	h = 600; 
	
	for (int j = 0; j <= num_boxes; j++) {
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
	checker_ptr->set_size(wx); 
	checker_ptr->set_color1(0.7);  
	checker_ptr->set_color2(white);
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.15);
	sv_matte_ptr1->set_kd(1.0); 
	sv_matte_ptr1->set_cd(checker_ptr);	
	Plane* plane_ptr = new Plane(Point3D(0, 1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr1);
	add_object(plane_ptr);
}
