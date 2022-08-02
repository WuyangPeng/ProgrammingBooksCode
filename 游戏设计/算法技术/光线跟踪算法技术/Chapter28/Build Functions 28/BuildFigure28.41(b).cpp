// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the Scene for Figure 28.41(b)

// This takes a huge time to render
// try 150 x 150 pixels, one sample per pixel, and max_depth = 6.

void 												
World::build(void) {
	int num_samples = 9;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(10);   
	
	tracer_ptr = new Whitted(this);
	
	background_color = RGBColor(0.9);  
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-0.5, -1.0, 4); 
	pinhole_ptr->set_lookat(0.0); 
	pinhole_ptr->set_view_distance(900.0); 			
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 25, 10); 
	light_ptr1->scale_radiance(2.5);  
	light_ptr1->set_shadows(true);   
	add_light(light_ptr1);
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(-1, 0, 0);    
	light_ptr2->scale_radiance(2.5);  
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	

	// fishbowl
	
	// glass-air interface
	
	float c = 2;
	RGBColor glass_color(0.27*c, 0.49*c, 0.42*c);   
	RGBColor water_color(0.75, 1, 0.75);
	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_ks(0.5);
	glass_ptr->set_exp(8000.0);  
	glass_ptr->set_eta_in(1.50);			// glass
	glass_ptr->set_eta_out(1.0);			// air
	glass_ptr->set_cf_in(glass_color);
	glass_ptr->set_cf_out(white); 
		
	// water-air interface
	
	Dielectric* water_ptr = new Dielectric;
	water_ptr->set_ks(0.5);
	water_ptr->set_exp(8000);
	water_ptr->set_eta_in(1.33);			// water
	water_ptr->set_eta_out(1.0);			// air
	water_ptr->set_cf_in(water_color);
	water_ptr->set_cf_out(white);

	// water-glass interface

	Dielectric* dielectric_ptr1 = new Dielectric;
	dielectric_ptr1->set_ks(0.5);
	dielectric_ptr1->set_exp(8000);
	dielectric_ptr1->set_eta_in(1.33); 		// water
	dielectric_ptr1->set_eta_out(1.5); 		// glass
	dielectric_ptr1->set_cf_in(water_color);
	dielectric_ptr1->set_cf_out(glass_color);
	
	// physical bowl parameters (also the defaults)
	
	double inner_radius		= 1.0;
	double glass_thickness	= 0.1;
	double water_depth		= 1.25;
	double meniscus_radius 	= 0.05;
	double opening_angle 	= 90.0;
	
	
	FishBowl* fishbowl_ptr = new FishBowl(	inner_radius,
											glass_thickness,
											water_depth,
											meniscus_radius,
											opening_angle);
	fishbowl_ptr->set_glass_air_material(glass_ptr);
	fishbowl_ptr->set_water_air_material(water_ptr);
	fishbowl_ptr->set_water_glass_material(dielectric_ptr1);
	add_object(fishbowl_ptr);
	

	
	// goldfish
	
	Phong* phong_ptr1 = new Phong;			
	phong_ptr1->set_ka(0.4); 
	phong_ptr1->set_kd(0.8); 
	phong_ptr1->set_cd(1.0, 0.15, 0.0);   	// orange 
	phong_ptr1->set_ks(0.5);
	phong_ptr1->set_cs(1.0, 0.35, 0.0);		// orange
	phong_ptr1->set_exp(50.0); 
	phong_ptr1->set_shadows(false); 
	
	
	// we read the fish file once, and instance it
		
//	const char* file_name = "goldfish_low_res.ply";		// for scene design
	const char* file_name = "goldfish_high_res.ply";	// for production
	Grid* grid_ptr = new Grid(new Mesh);
//	grid_ptr->read_flat_triangles(file_name);		
	grid_ptr->read_smooth_triangles(file_name);		
	grid_ptr->set_material(phong_ptr1);    
	grid_ptr->setup_cells();
	
	Instance* gold_fish_ptr1 = new Instance(grid_ptr);
	gold_fish_ptr1->scale(0.03);
	gold_fish_ptr1->rotate_y(-45);
	gold_fish_ptr1->translate(0.5, 0.0, 0.0);
	add_object(gold_fish_ptr1);
	
	Instance* goldfish_ptr2 = new Instance(grid_ptr);
	goldfish_ptr2->scale(0.02);
	goldfish_ptr2->rotate_y(90);
	goldfish_ptr2->translate(-0.75, 0.0, 0.0);
	goldfish_ptr2->rotate_y(-60);
	add_object(goldfish_ptr2);
	
	Instance* goldfish_ptr3 = new Instance(grid_ptr);
	goldfish_ptr3->scale(0.02);
	goldfish_ptr3->rotate_x(20);
	goldfish_ptr3->rotate_y(-45);
	goldfish_ptr3->translate(-0.1, -0.4, 0.0);
	add_object(goldfish_ptr3);
	
	
	// cylinder under the bowl
	
	Phong* phong_ptr2 = new Phong;			
	phong_ptr2->set_ka(0.4); 
	phong_ptr2->set_kd(0.8); 
	phong_ptr2->set_cd(0.05); 
	phong_ptr2->set_ks(0.2); 
	phong_ptr2->set_exp(100.0);  
	
	double bottom = -1.2;
	double radius = 0.5;
	double top = -sqrt(1.1 * 1.1 - radius * radius);
	
	ConvexOpenCylinder* cylinder_ptr = new ConvexOpenCylinder(bottom, top, radius);
	cylinder_ptr->set_material(phong_ptr2);
	add_object(cylinder_ptr);
	
	
	// single air bubble
	
	Dielectric* dielectric_ptr2 = new Dielectric;
	dielectric_ptr2->set_eta_in(1.0); 		// air
	dielectric_ptr2->set_eta_out(1.33); 	// water
	dielectric_ptr2->set_cf_in(white);
	dielectric_ptr2->set_cf_out(water_color);
	
	Sphere* bubble_ptr = new Sphere(Point3D(0.2, 0.2, 0.2), 0.05);
	bubble_ptr->set_material(dielectric_ptr2);
	add_object(bubble_ptr);
	
	
	// streams of air bubbles
	
	set_rand_seed(1000);
	
	double bubble_radius		= 0.045;         	
	double yc_bottom 			= -0.9;    			// height of bottom bubble center
	double yc_top 				= 0.2;    			// height of top bubble center
	double num_bubbles 			= 8;				// number of bubbles in stream
	double spacing 				= (yc_top - yc_bottom) / num_bubbles; // vertical spacing between bubble centers
	double translation_factor 	= bubble_radius / 2.0;
	double min 					= 0.9;   			// minimum bubble scaling
	double max 					= 1.1;				// maximum bubble scaling
	double xc 					= -0.1;   			// center x 
	double zc 					= 0.3;				// center y
	
	
	
	// bubble stream 1
		
	Grid* bubble_stream_ptr_1 = new Grid;
	
	for (int j = 0; j <= num_bubbles; j++) {		
		Instance* bubble_ptr = new Instance(new Sphere);

		bubble_ptr->scale(	min + rand_float() * (max - min), 
							min + rand_float() * (max - min),
							min + rand_float() * (max - min));
				
		bubble_ptr->scale(bubble_radius);
		
		bubble_ptr->rotate_x(360.0 * rand_float());
		bubble_ptr->rotate_y(360.0 * rand_float());
		bubble_ptr->rotate_z(360.0 * rand_float());  
		
		bubble_ptr->translate(	xc + (2.0 * rand_float() - 1.0) * translation_factor, 
								yc_bottom + j * spacing + (2.0 * rand_float() - 1.0) * translation_factor,
								zc + (2.0 * rand_float() - 1.0) * translation_factor);					
				
		bubble_ptr->set_material(dielectric_ptr2);
		bubble_stream_ptr_1->add_object(bubble_ptr);
	}
		
	bubble_stream_ptr_1->setup_cells();
	add_object(bubble_stream_ptr_1);
	
	
	
	// bubble stream 2 
	
	num_bubbles = 7;
	xc = 0.075; 
	zc = 0.1;
	
	Grid* bubble_stream_ptr_2 = new Grid;
	
	for (int j = 0; j <= num_bubbles; j++) {
		Instance* bubble_ptr = new Instance(new Sphere);
	
		bubble_ptr->scale(	min + rand_float() * (max - min), 
							min + rand_float() * (max - min),
							min + rand_float() * (max - min));
				
		bubble_ptr->scale(bubble_radius);
		
		bubble_ptr->rotate_x(360.0 * rand_float());
		bubble_ptr->rotate_y(360.0 * rand_float());
		bubble_ptr->rotate_z(360.0 * rand_float());  
		
		bubble_ptr->translate(	xc + (2.0 * rand_float() - 1.0) * translation_factor, 
								yc_bottom + j * spacing + (2.0 * rand_float() - 1.0) * translation_factor,
								zc + (2.0 * rand_float() - 1.0) * translation_factor);					
				
		bubble_ptr->set_material(dielectric_ptr2);
		bubble_stream_ptr_2->add_object(bubble_ptr);
	}
	
	bubble_stream_ptr_2->setup_cells();
	add_object(bubble_stream_ptr_2);
	
	
	
	// bubble stream 3 
	
	num_bubbles = 9;
	xc = -0.15;
	zc = -0.3;
	
	Grid* bubble_stream_ptr_3 = new Grid;
	
	for (int j = 0; j <= num_bubbles; j++) {
		Instance* bubble_ptr = new Instance(new Sphere);
	
		bubble_ptr->scale(	min + rand_float() * (max - min), 
							min + rand_float() * (max - min),
							min + rand_float() * (max - min));
				
		bubble_ptr->scale(bubble_radius);
		
		bubble_ptr->rotate_x(360.0 * rand_float());
		bubble_ptr->rotate_y(360.0 * rand_float());
		bubble_ptr->rotate_z(360.0 * rand_float());  
		
		bubble_ptr->translate(	xc + (2.0 * rand_float() - 1.0) * translation_factor, 
								yc_bottom + j * spacing + (2.0 * rand_float() - 1.0) * translation_factor,
								zc + (2.0 * rand_float() - 1.0) * translation_factor);					
				
		bubble_ptr->set_material(dielectric_ptr2);
		bubble_stream_ptr_3->add_object(bubble_ptr);
	}
	
	bubble_stream_ptr_3->setup_cells();
	add_object(bubble_stream_ptr_3);
	
	
	
	
	// plane
	
	PlaneChecker* checker_ptr = new PlaneChecker;
	checker_ptr->set_size(0.5);		
	checker_ptr->set_outline_width(0.05);
	checker_ptr->set_color1(0.75);
	checker_ptr->set_color2(0.75);  
	checker_ptr->set_outline_color(0.45); 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.5);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -1.2, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr);
	
	Instance* plane_ptr2 = new Instance(plane_ptr); // to adjust the reflection of the grid lines off the top of the water
	plane_ptr2->rotate_y(30);
	plane_ptr2->translate(0.25, 0, 0.15);
	add_object(plane_ptr2);
}


