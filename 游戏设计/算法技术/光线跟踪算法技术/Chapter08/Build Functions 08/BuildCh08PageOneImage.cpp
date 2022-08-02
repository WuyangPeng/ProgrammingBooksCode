// This builds the scene for the Chapter 8 page one image
// Note the perspective distortion of the spheres
// This figure is the same as Figure 8.21(c).

void 											
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(500);			
	vp.set_vres(500);
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	
	background_color = black;
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 2, 0); 
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->set_view_distance(73.0);
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
		
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 1, 1);
	light_ptr->scale_radiance(3.0);
	add_light(light_ptr);
	
	// construct the spheres
	
	float d = 2.0; 		// sphere center spacing 
	float r = 0.75; 	// sphere radius
	float xc, yc; 		// sphere center coordinates
	int num_rows = 5;
	int num_columns = 5;
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(0.5);
	checker_ptr->set_color1(0,0.4,0.8);
	checker_ptr->set_color2(1,1,1);
			
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.2);
	sv_matte_ptr->set_kd(0.8);
	sv_matte_ptr->set_cd(checker_ptr);
	
	for (int k = 0; k < num_columns; k++) 		// up
		for (int j = 0; j < num_rows; j++) {	// across
				Sphere*	sphere_ptr = new Sphere();
				xc = d * (j - (num_columns - 1) / 2.0);
				yc = d * (k - (num_rows - 1) / 2.0);
				sphere_ptr->set_center(xc, 0, yc);
				sphere_ptr->set_radius(r);		
				sphere_ptr->set_material(sv_matte_ptr);
				add_object(sphere_ptr);
		}	
}




