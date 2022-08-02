// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.42

void 												
World::build(void) {
	int num_samples = 16;

	vp.set_hres(800);     
	vp.set_vres(400);    	
	vp.set_max_depth(1);
	vp.set_samples(num_samples);
	
	background_color = black;
	tracer_ptr = new Whitted(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 30, 100);
	pinhole_ptr->set_lookat(-0.01, 0.09, 0);
	pinhole_ptr->set_view_distance(173333.0); 	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
	
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(1, 1, 4);		
	light_ptr->scale_radiance(3.0);
	add_light(light_ptr);
	
	
	const char* file_name = "Bunny16K.ply"; 
	
	Grid* grid_ptr = new Grid(new Mesh);
	grid_ptr->read_smooth_triangles(file_name);
	grid_ptr->setup_cells();
	
	
	// center bunny:
	
	Image* image_ptr1 = new Image;						
	image_ptr1->read_ppm_file("TurquoiseAndBrownRamp.ppm");
	
	
	// noise:
	
	CubicNoise* noise_ptr1 = new CubicNoise;	
	noise_ptr1->set_num_octaves(4);
	noise_ptr1->set_gain(0.5);	
	noise_ptr1->set_lacunarity(2.0);	


	// texture:
		
	WrappedRamp* wrapped_ptr1 = new WrappedRamp(image_ptr1);
	wrapped_ptr1->set_noise(noise_ptr1);
	wrapped_ptr1->set_perturbation(6.0);
	wrapped_ptr1->set_wrap_number(8.0);
	
	TInstance* texture_ptr1 = new TInstance(wrapped_ptr1);
	texture_ptr1->scale(0.1);
	

	// material:
	
	SV_Matte* sv_matte_ptr1 = new SV_Matte;		
	sv_matte_ptr1->set_ka(0.15);
	sv_matte_ptr1->set_kd(0.85);
	sv_matte_ptr1->set_cd(texture_ptr1);
	
	
	Instance* bunny_ptr1 = new Instance(grid_ptr);
	bunny_ptr1->set_material(sv_matte_ptr1);
	bunny_ptr1->rotate_y(25);
	add_object(bunny_ptr1);	
	


	
	// left bunny 
	
	Image* image_ptr2 = new Image;						
	image_ptr2->read_ppm_file("BlueAndBuffRamp.ppm");
	
	
	// noise:
	
	CubicNoise* noise_ptr2 = new CubicNoise;	
	noise_ptr2->set_num_octaves(4);
	noise_ptr2->set_gain(0.5);	
	noise_ptr2->set_lacunarity(3.0);	

	
	// texture:
	
	WrappedRamp* wrapped_ptr2 = new WrappedRamp(image_ptr2);
	wrapped_ptr2->set_noise(noise_ptr2);
	wrapped_ptr2->set_perturbation(6.0);
	wrapped_ptr2->set_wrap_number(8.0);
	
	TInstance* texture_ptr2 = new TInstance(wrapped_ptr2);
	texture_ptr2->scale(0.075);


	// material:
	
	SV_Matte* sv_matte_ptr2 = new SV_Matte;		
	sv_matte_ptr2->set_ka(0.15);
	sv_matte_ptr2->set_kd(0.85);
	sv_matte_ptr2->set_cd(texture_ptr2);
	
	
	Instance* bunny_ptr2 = new Instance(grid_ptr);
	bunny_ptr2->set_material(sv_matte_ptr2);
	bunny_ptr2->rotate_y(25);
	bunny_ptr2->translate(-0.15, 0.0, 0.0);
	add_object(bunny_ptr2);	
	
	
	// right bunny:
	
	Image* image_ptr3 = new Image;						
	image_ptr3->read_ppm_file("BrownRamp.ppm");
	
	
	// noise:
	
	CubicNoise* noise_ptr3 = new CubicNoise;	
	noise_ptr3->set_num_octaves(4);
	noise_ptr3->set_gain(0.5);	
	noise_ptr3->set_lacunarity(5.0);

	
	// texture:
	
	WrappedRamp* wrapped_ptr3 = new WrappedRamp(image_ptr3);
	wrapped_ptr3->set_noise(noise_ptr3);
	wrapped_ptr3->set_perturbation(6.0);
	wrapped_ptr3->set_wrap_number(8.0);
	
	TInstance* texture_ptr3 = new TInstance(wrapped_ptr3);
	texture_ptr3->scale(0.3);


	// material:
	
	SV_Matte* sv_matte_ptr3 = new SV_Matte;		
	sv_matte_ptr3->set_ka(0.15);
	sv_matte_ptr3->set_kd(0.85);
	sv_matte_ptr3->set_cd(texture_ptr3);
	
	
	Instance* bunny_ptr3 = new Instance(grid_ptr);
	bunny_ptr3->set_material(sv_matte_ptr3);
	bunny_ptr3->rotate_y(25);
	bunny_ptr3->translate(0.15, 0.0, 0.0);
	add_object(bunny_ptr3);	
	

	// reflective ground plane
	
	Reflective*	reflective_ptr = new Reflective;			
	reflective_ptr->set_ka(0.2); 
	reflective_ptr->set_kd(0.75);
	reflective_ptr->set_cd(black);
	reflective_ptr->set_ks(0.0);
	reflective_ptr->set_exp(20);
	reflective_ptr->set_kr(0.5);  
	reflective_ptr->set_cr(0.8, 1.0, 0.8);    
		
	Plane* plane_ptr = new Plane(Point3D(0, 0.033, 0), Normal(0, 1, 0));	
	plane_ptr->set_material(reflective_ptr);
	add_object(plane_ptr);
	
}



