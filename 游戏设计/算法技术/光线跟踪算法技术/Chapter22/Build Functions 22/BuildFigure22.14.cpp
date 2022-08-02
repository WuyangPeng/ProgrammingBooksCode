// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This constructs the scene for Figure 22.14
// The grid lines on the spheres are rendered with a 2D SphereChecker texture
// See Section 30.2.2 and Exercise 30.4
// This texture can only be applied to a unit sphere at the origin

void 												
World::build(void) {
	int num_samples = 1;
	
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
	
	int num_spheres	= 25;
	float volume = 0.1 / num_spheres;
	float radius = 2.5 * pow(0.75 * volume / 3.14159, 0.333333);
	
	set_rand_seed(15);  
	
	for (int j = 0; j < num_spheres; j++) {
		SphereChecker* checker_ptr = new SphereChecker;
		checker_ptr->set_numlong(20);
		checker_ptr->set_numlat(10);
		checker_ptr->set_line_width(0.05);
		
		RGBColour color(rand_float(), rand_float(), rand_float());
		checker_ptr->set_color1(color);
		checker_ptr->set_color2(color);
		checker_ptr->set_line_color(black);
		
		SV_Matte* sv_matte_ptr1 = new SV_Matte;		
		sv_matte_ptr1->set_ka(0.25);
		sv_matte_ptr1->set_kd(0.85);
		sv_matte_ptr1->set_cd(checker_ptr);
		
		Sphere* sphere_ptr1 = new Sphere;
		sphere_ptr1->set_material(sv_matte_ptr1);
		
		Instance* sphere_ptr2 = new Instance(sphere_ptr1);
		sphere_ptr2->scale(radius);
		sphere_ptr2->translate(1.0 - 2.0 * rand_float(), 1.0 - 2.0 * rand_float(), 1.0 - 2.0 * rand_float());
		sphere_ptr2->set_bounding_box();
		
		grid_ptr->add_object(sphere_ptr2);
	}	
	
	grid_ptr->setup_cells();
	add_object(grid_ptr);	
}


