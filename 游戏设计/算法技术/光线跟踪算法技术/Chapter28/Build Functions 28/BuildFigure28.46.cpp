// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.26

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(3);
	
	background_color = black;  
	
	tracer_ptr = new Whitted(this);
		
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);	

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-1.45, 25, 22.5);  
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(3000);  
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
		

	// point light 
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 50, 0); 
	light_ptr1->scale_radiance(5.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	

	// point light 
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-10, 20, 10); 
	light_ptr2->scale_radiance(4.0);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	
	// directional light 
	
	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(-1, 0, 0); 
	light_ptr3->scale_radiance(4.0);
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);
	
	
	// checker sphere
	
	// 2D sphere checker texture
	
	SphereChecker* checker_ptr1 = new SphereChecker;
	checker_ptr1->set_num_horizontal(12); 
	checker_ptr1->set_num_vertical(12);  
	checker_ptr1->set_horizontal_line_width(0.075);
	checker_ptr1->set_vertical_line_width(0.075);
	checker_ptr1->set_color1(white);
	checker_ptr1->set_color2(0.75);
	checker_ptr1->set_line_color(black);

	// spatially varying self-emissive material
	
	SV_Emissive* sv_emissive_ptr = new SV_Emissive;
	sv_emissive_ptr->scale_radiance(20.0);	
	sv_emissive_ptr->set_ce(checker_ptr1);		
		
	Sphere* sphere_ptr1 = new Sphere;
	sphere_ptr1->set_material(sv_emissive_ptr);   
	
	Instance* big_sphere_ptr = new Instance(sphere_ptr1);
	big_sphere_ptr->scale(30.0);
	big_sphere_ptr->translate(0, 50, 45);
	add_object(big_sphere_ptr);
	
	
	// transparent sphere with grid lines
	
	// emissive material for the grid lines 
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(0.85);
	emissive_ptr->set_ce(1, 0.7, 0);		// orange
	
	
	// dielectric material for the checkers
	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_ks(0.2);
	glass_ptr->set_exp(1000.0);
	glass_ptr->set_eta_in(1.5);
	glass_ptr->set_eta_out(1.0);
	glass_ptr->set_cf_in(0.5, 0.95, 0.92);   	
	glass_ptr->set_cf_out(white);

	// SphereMaterials material to store the grid lines and the transparent checkers
	// See the Figure 24.15(c) build function for information on this material
	
	SphereMaterials* sphere_materials_ptr = new SphereMaterials;
	sphere_materials_ptr->set_num_horizontal(12);  
	sphere_materials_ptr->set_num_vertical(6);		
	sphere_materials_ptr->set_line_width(0.03);    
	sphere_materials_ptr->set_checker1_material(glass_ptr);
	sphere_materials_ptr->set_checker2_material(glass_ptr);
	sphere_materials_ptr->set_line_material(emissive_ptr);
	
	Sphere* sphere_ptr3 = new Sphere;
	sphere_ptr3->set_material(sphere_materials_ptr);   

	Instance* sphere_ptr4 = new Instance(sphere_ptr3);
	sphere_ptr4->scale(3.0);
	add_object(sphere_ptr4);
}


