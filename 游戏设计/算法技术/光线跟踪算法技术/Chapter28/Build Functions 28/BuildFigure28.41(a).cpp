// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.41(a)

// This takes a huge amount of time to render

void 												
World::build(void) {
	int num_samples = 9;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(10);  
	
	tracer_ptr = new Whitted(this);
	
	background_color = RGBColor(0.75);  
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(4.5, 6, 4); 
	pinhole_ptr->set_lookat(0.0); 
	pinhole_ptr->set_view_distance(1800.0);  			
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 25, -10); 
	light_ptr1->scale_radiance(5.0);  
	light_ptr1->set_shadows(true);   
	add_light(light_ptr1);
	

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

	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ks(0.5);
	dielectric_ptr->set_exp(8000);
	dielectric_ptr->set_eta_in(1.33); 		// water
	dielectric_ptr->set_eta_out(1.5); 		// glass
	dielectric_ptr->set_cf_in(water_color);
	dielectric_ptr->set_cf_out(glass_color);
	
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
	fishbowl_ptr->set_water_glass_material(dielectric_ptr);
	add_object(fishbowl_ptr);
	

	
	// goldfish
	
	Phong* phong_ptr = new Phong;			
	phong_ptr->set_ka(0.4); 
	phong_ptr->set_kd(0.8); 
	phong_ptr->set_cd(1.0, 0.15, 0.0);   	// orange 
	phong_ptr->set_ks(0.5);  
	phong_ptr->set_cs(1.0, 0.35, 0.0);		// orange
	phong_ptr->set_exp(50.0); 
	phong_ptr->set_shadows(false); 
	
		
//	const char* file_name = "goldfish_low_res.ply";		// for scene design
	const char* file_name = "goldfish_high_res.ply";  // for production
	Grid* grid_ptr = new Grid(new Mesh);
//	grid_ptr->read_flat_triangles(file_name);		
	grid_ptr->read_smooth_triangles(file_name);		
	grid_ptr->set_material(phong_ptr);    
	grid_ptr->setup_cells();
	
	Instance* gold_fish_ptr = new Instance(grid_ptr);
	gold_fish_ptr->scale(0.03);
	gold_fish_ptr->translate(0.5, 0.0, 0.0);
	add_object(gold_fish_ptr);
	
	
	// plane
	
	PlaneChecker* checker_ptr = new PlaneChecker;
	checker_ptr->set_size(0.5);		
	checker_ptr->set_outline_width(0.05);
	checker_ptr->set_color1(0.75);
	checker_ptr->set_color2(0.75);  
	checker_ptr->set_outline_color(0.45); 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.65);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -1.51, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);
}


