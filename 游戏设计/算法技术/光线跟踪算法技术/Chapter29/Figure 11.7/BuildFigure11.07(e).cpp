// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 11.7(e)

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	FishEye* fisheye_ptr = new FishEye;
	fisheye_ptr->set_eye(250, 450, 150); 
	fisheye_ptr->set_lookat(-20, 250, -110);  
	fisheye_ptr->set_fov(360);
	fisheye_ptr->compute_uvw();  
	set_camera(fisheye_ptr);


	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(150, 200, 65);  
	light_ptr1->scale_radiance(5.25);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	
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
	
	int num_boxes = 40;
	float wx = 50;
	float wz = 50;
	float h = 150;
	float s = 100;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx, 0, -(j + 1) * wz - j * s), 
								Point3D(0, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr1);
	//	add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// second row
	
	h = 300;
	
	for (int j = 0; j < num_boxes; j++) {
		Box* box_ptr = new Box(	Point3D(-wx -wx - s, 0, -(j + 1) * wz - j * s), 
								Point3D(-wx - s, h, - j * wz - j * s));
		box_ptr->set_material(matte_ptr2);
//		add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	
	// third row
	
	h = 850; 
	
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
		box_ptr->set_material(matte_ptr1);
//		add_object(box_ptr);
		grid_ptr->add_object(box_ptr);
	}
	
	grid_ptr->setup_cells();
	add_object(grid_ptr);
	
	
	// ground plane with checker
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(2 * wx); 
	checker_ptr->set_color1(0.7);  
	checker_ptr->set_color2(white);
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.20);
	sv_matte_ptr1->set_kd(0.50); 
	sv_matte_ptr1->set_cd(checker_ptr);	
	Plane* plane_ptr = new Plane(Point3D(0, 1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr1);
	add_object(plane_ptr);

	
	// skydome with clouds
	
	Image* image_ptr = new Image;						
	image_ptr->read_ppm_file("CloudsHighRes.ppm");	
	
	HemisphericalMap* hemispherical_ptr = new HemisphericalMap; 
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(hemispherical_ptr);
	

	SV_Emissive* sv_emissive_ptr = new SV_Emissive;
	sv_emissive_ptr->set_ce(image_texture_ptr);
	sv_emissive_ptr->scale_radiance(1.0);
	
	Instance* hemisphere_ptr = new Instance(new ConcaveHemisphere); 
	hemisphere_ptr->scale(1000000.0);
	hemisphere_ptr->set_material(sv_emissive_ptr);
	add_object(hemisphere_ptr);
}


