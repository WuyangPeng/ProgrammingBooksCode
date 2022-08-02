// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds Figure9.10

void 												
World::build(void) {
	vp.set_hres(400);			
	vp.set_vres(400);
	vp.set_samples(25);
	
	tracer_ptr = new RayCast(this);
			
	Pinhole* camera_ptr = new Pinhole;
	
	// Figure9.10(a)
/*	
	camera_ptr->set_eye(150, 195, 125);
	camera_ptr->set_lookat(0, 195, -40);
	camera_ptr->set_view_distance(167);
*/	
/*		
	// Figure9.10(b)
		
	camera_ptr->set_eye(150, 300, 125);   
	camera_ptr->set_lookat(0, 265, -40);  
	camera_ptr->set_view_distance(167);
*/

	// Figure9.10(c)
		
	camera_ptr->set_eye(-250, 350, 500);   
	camera_ptr->set_lookat(-250, 350, 0);  
	camera_ptr->set_view_distance(280);

	camera_ptr->compute_uvw(); 
	set_camera(camera_ptr);

	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(150, 200, 65);   
	light_ptr1->scale_radiance(5.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_cd(0, 0.5, 0.5);     // cyan
	matte_ptr1->set_ka(0.4); 
	matte_ptr1->set_kd(0.5); 
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_cd(0.8, 0.5, 0);     // orange
	matte_ptr2->set_ka(0.4); 
	matte_ptr2->set_kd(0.5);  
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_cd(0.5, 0.6, 0);     // green
	matte_ptr3->set_ka(0.4); 
	matte_ptr3->set_kd(0.5); 
	
	
	// construct rows of boxes parallel to the zw axis
	
	Grid* grid_ptr = new Grid;
	
	// first row
	
	int num_boxes = 40;
	float wx = 50;
	float wz = 50;
	float h = 150;
	float s = 100;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx, 0, -(j + 1) * wz - j * s), 
								Point3D(0, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr2);
	//	add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// second row
	
	h = 300;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx -wx - s, 0, -(j + 1) * wz - j * s), 
								Point3D(-wx - s, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr1);
//		add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// third row
	
	h = 600;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx - 2 * wx - 2 * s, 0, -(j + 1) * wz - j * s), 
								Point3D(-2 * wx - 2 * s, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr3);
//		add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// a column
	
	h = 150;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-3 * (wx + s) - (j + 1) * wz - j * s, 0, -wx), 
								Point3D(-3 * (wx + s) - j * wz - j * s, h, 0));
		box_ptr->set_material(matte_ptr2);
//		add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	grid_ptr->setup_cells();
	add_object(grid_ptr);
	
	
	// ground plane with checker:
	
	Checker3D* checker3D_ptr = new Checker3D;
	checker3D_ptr->set_size(wx); 
	checker3D_ptr->set_color1(0.7);  
	checker3D_ptr->set_color2(1.0);

	SV_Matte* sv_matte_ptr = new SV_Matte;
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.35);
	sv_matte_ptr->set_cd(checker3D_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, 1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);


}




