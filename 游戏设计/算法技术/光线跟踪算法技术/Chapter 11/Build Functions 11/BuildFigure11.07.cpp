// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 11.7
// It uses a grid acceleration scheme (Chapter 22), a spherical texture mapping (Chapter 29),
// and a 3D checker (Chapter 30).
// You can test the fisheye camera without these features by doing the following:
// remove the grid code
// add the boxes directly to the world (I've left commented out code for doing this)
// don't use the skydome. This will give you a black background like the boxes image in 
// Chapter 9
// use a Matte material on the plane

// The code for the image class is in the Chapter 29 directory


void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	// pinhole camera for Figure 11.7(a)
			
	Pinhole* pinHole_ptr = new Pinhole;
	pinHole_ptr->set_eye(250, 300, 150); 
	pinHole_ptr->set_lookat(-20, 300, -110);  
	pinHole_ptr->set_view_distance(250);
	pinHole_ptr->compute_uvw();  
//	set_camera(pinHole_ptr);
		
	
	// fisheye camera for the other parts
	
	FishEye* fisheye_ptr = new FishEye;
	
	// for parts (b), (c), (d)
	
	fisheye_ptr->set_eye(250, 300, 150);
	fisheye_ptr->set_lookat(-20, 300, -110);
	fisheye_ptr->set_fov(120);  // part (b)
//	fisheye_ptr->set_fov(180);  // part (c)
//	fisheye_ptr->set_fov(360);  // part (d)
   

/*	
	
	// for part (e)
	
	fisheye_ptr->set_eye(250, 450, 150); 
	fisheye_ptr->set_lookat(-20, 250, -110);  
	fisheye_ptr->set_fov(360);
	
*/


/*	
	// for part (f)
	// for this image the skydome is the only object in the scene
	// you need to comment out the two statements:
	// add_object(grid_ptr);
	// add_object(plane_ptr);
	
	fisheye_ptr->set_eye(0, 0, 0);     
	fisheye_ptr->set_lookat(0, 1, 0);
	fisheye_ptr->set_fov(180);
*/	
		
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
	image_ptr->read_ppm_file("CloudsSmall.ppm");
	
	SphericalMap* spherical_map_ptr = new SphericalMap; 
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(spherical_map_ptr);
	
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(1);
	sv_matte_ptr2->set_kd(0.85);
	sv_matte_ptr2->set_cd(image_texture_ptr);	
	
	Instance* sphere_ptr1 = new Instance(new Sphere); 
	sphere_ptr1->scale(1000000);
	sphere_ptr1->set_material(sv_matte_ptr2);
	add_object(sphere_ptr1);
}




