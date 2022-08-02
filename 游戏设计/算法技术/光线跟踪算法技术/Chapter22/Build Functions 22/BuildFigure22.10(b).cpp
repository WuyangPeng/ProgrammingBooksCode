// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 22.10(b)

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(800);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Spherical* spherical_ptr = new Spherical;
	spherical_ptr->set_eye(0, 0, 0);       
	spherical_ptr->set_lookat(-100, 0, 0);
	spherical_ptr->set_horizontal_fov(360);     
	spherical_ptr->set_vertical_fov(180);
	spherical_ptr->compute_uvw();
	set_camera(spherical_ptr);

	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(1, 0, 0);    				// from the +ve x direction     
	light_ptr1->scale_radiance(1);   
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(0, 1, 0);    				// from the +ve y direction     
	light_ptr2->scale_radiance(2);   
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);	
	
	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(0, 0, 1);    				// from the +ve z direction      
	light_ptr3->scale_radiance(1.5);   
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);
	
	
	Directional* light_ptr4 = new Directional;
	light_ptr4->set_direction(-1, 0, 0);    			// from the -ve x direction     
	light_ptr4->scale_radiance(1);   
	light_ptr4->set_shadows(true);
	add_light(light_ptr4);
	
	Directional* light_ptr5 = new Directional;
	light_ptr5->set_direction(0, -1, 0);    			// from the -ve y direction     
	light_ptr5->scale_radiance(2);   
	light_ptr5->set_shadows(true);
	add_light(light_ptr5);	
	
	Directional* light_ptr6 = new Directional;
	light_ptr6->set_direction(0, 0, -1);    			// from the -ve z direction      
	light_ptr6->scale_radiance(1.5);   
	light_ptr6->set_shadows(true);
	add_light(light_ptr6);
	
	
	Grid* grid_ptr = new Grid;

	// eight boxes
	
	// bottom four
	
	float bottom_size = 0.5;
	Vector3D diagonal(bottom_size, bottom_size, bottom_size);
	Point3D p0;
	
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.5);   // gray
		
	p0 = Point3D(-1, -1, -1);
	Box* box_ptr1 = new Box(p0, p0 + diagonal); 
	box_ptr1->set_material(matte_ptr1);
	grid_ptr->add_object(box_ptr1);
	
		
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.25);
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(1, 0, 0);  // red
	
	p0 = Point3D(-1, -1, 1 - bottom_size);
	Box* box_ptr2 = new Box(p0, p0 + diagonal); 
	box_ptr2->set_material(matte_ptr2);
	grid_ptr->add_object(box_ptr2);
	
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.25);
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(1, 1, 0);  // yellow
	
	p0 = Point3D(1 - bottom_size, -1, 1 - bottom_size);
	Box* box_ptr3 = new Box(p0, p0 + diagonal); 
	box_ptr3->set_material(matte_ptr3);
	grid_ptr->add_object(box_ptr3);
	
	
	Matte* matte_ptr4 = new Matte;
	matte_ptr4->set_ka(0.25);
	matte_ptr4->set_kd(0.75);
	matte_ptr4->set_cd(0.2, 0.6, 0.4);  // green
	
	p0 = Point3D(1 - bottom_size, -1, -1);
	Box* box_ptr4 = new Box(p0, p0 + diagonal); 
	box_ptr4->set_material(matte_ptr4);
	grid_ptr->add_object(box_ptr4);
	
	
	// top four
	
	float top_size = 0.35;
	diagonal = Vector3D(top_size, top_size, top_size);
	
	Matte* matte_ptr5 = new Matte;
	matte_ptr5->set_ka(0.25);
	matte_ptr5->set_kd(0.75);
	matte_ptr5->set_cd(0.27, 0.36, 1.0);  // blue
	
	p0 = Point3D(-1, 1 - top_size, -1);
	Box* box_ptr5 = new Box(p0, p0 + diagonal); 
	box_ptr5->set_material(matte_ptr5);
	grid_ptr->add_object(box_ptr5);

	
	Matte* matte_ptr6 = new Matte;
	matte_ptr6->set_ka(0.25);
	matte_ptr6->set_kd(0.75);
	matte_ptr6->set_cd(0.75, 0, 0.75);  // majenta
	
	p0 = Point3D(-1, 1 - top_size, 1 - top_size);
	Box* box_ptr6 = new Box(p0, p0 + Vector3D(0.25, top_size, top_size)); 
	box_ptr6->set_material(matte_ptr6);
	grid_ptr->add_object(box_ptr6);
	
	
	Matte* matte_ptr7 = new Matte;
	matte_ptr7->set_ka(0.25);
	matte_ptr7->set_kd(0.75);
	matte_ptr7->set_cd(1, 1, 1);  // white
	
	p0 = Point3D(1 - 0.25, 1 - 0.25, 1 - 0.25);
	Box* box_ptr7 = new Box(p0, p0 + Vector3D(0.25)); 
	box_ptr7->set_material(matte_ptr7);
	grid_ptr->add_object(box_ptr7);
	
	
	Matte* matte_ptr8 = new Matte;
	matte_ptr8->set_ka(0.25);
	matte_ptr8->set_kd(0.75);
	matte_ptr8->set_cd(0, 0.75, 0.75);  // cyan
	
	p0 = Point3D(1 - top_size, 1 - top_size, -1);
	Box* box_ptr8 = new Box(p0, p0 + Vector3D(top_size, top_size, 0.25)); 
	box_ptr8->set_material(matte_ptr8);
	grid_ptr->add_object(box_ptr8);
	
	grid_ptr->setup_cells();
	add_object(grid_ptr);	
}


