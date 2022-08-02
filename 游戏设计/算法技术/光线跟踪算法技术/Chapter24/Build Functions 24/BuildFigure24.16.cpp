// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 24.16
// It renders the left and right eye views

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(10);
	
	tracer_ptr = new Whitted(this);
	
	background_color = black; 
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);	
	
	float vpd = 2400.0;

	Pinhole* left_pinhole_ptr = new Pinhole;
	left_pinhole_ptr->set_view_distance(vpd);
	
	Pinhole* right_pinhole_ptr = new Pinhole;
	right_pinhole_ptr->set_view_distance(vpd);
	
	StereoCamera* stereo_ptr = new StereoCamera(left_pinhole_ptr, right_pinhole_ptr);
	stereo_ptr->use_parallel_viewing();
//	stereo_ptr->use_transverse_viewing();
	stereo_ptr->set_pixel_gap(5);
	stereo_ptr->set_eye(-8, 20, 40); 
	stereo_ptr->set_lookat(0, 4.5, 0); 
	stereo_ptr->compute_uvw(); 
	stereo_ptr->set_stereo_angle(1.5);  // in degrees
	stereo_ptr->setup_cameras(); 
	set_camera(stereo_ptr);
	
	
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
	
	
	
	// large emissive sphere with lines
	// this is not a light source 
	
	SphereChecker* checker_ptr1 = new SphereChecker;  // can only be applied to a generic sphere
	checker_ptr1->set_num_horizontal(16);
	checker_ptr1->set_num_vertical(16);    
	checker_ptr1->set_horizontal_line_width(0.075);
	checker_ptr1->set_vertical_line_width(0.075);
	checker_ptr1->set_color1(0.75, 1.0, 0.25);   // yellow
	checker_ptr1->set_color2(0.75, 1.0, 0.25);   // yellow
	checker_ptr1->set_line_color(black);
	
	SV_Emissive* sv_emissive_ptr = new SV_Emissive;
	sv_emissive_ptr->set_ce(checker_ptr1);
	sv_emissive_ptr->scale_radiance(1.5);      
	
		
	Sphere* sphere_ptr1 = new Sphere;
	sphere_ptr1->set_material(sv_emissive_ptr);
	
	Instance* sphere_ptr2 = new Instance(sphere_ptr1);
	sphere_ptr2->scale(30);
	sphere_ptr2->translate(0, 50, 45);
	add_object(sphere_ptr2);
	
	

	// reflective sphere
	
	// We use a SphereMaterials material for the reflective sphere.
	// This material is like the SphereChecker texture in that it can be used to render
	// checkers on a generic sphere, but it allows different materials to be used for the
	// the checkers and the lines.
	// You can implement this as an exercise.
	// In this figure, the reflective material in Figures 24.15(a) and (b) is used for 
	// both checkers, and a red emissive material is used for the lines.
	// A red Matte material for the lines is shaded from the three lights with the result that
	// the lines are not of constant brightness.
	// A reflective material for the lines with red for the diffuse and reflective colors is still
	// shaded, and also picks up the reflected colors from the emissive sphere and plane.
	// In contrast, an emissive material emits constant radiance, and is not reflective.
	
	Reflective* reflective_ptr = new Reflective;			
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.0); 
	reflective_ptr->set_cd(1.0);
	reflective_ptr->set_ks(0.15);
	reflective_ptr->set_exp(300.0);
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(1.0, 0.75, 0.25);  // orange
	
	Emissive* emissive_ptr = new Emissive;   
	emissive_ptr->set_ce(0.85);	
	emissive_ptr->set_ce(0, 0.75, 0);
	emissive_ptr->set_ce(0.85, 0, 0);		// red		
	emissive_ptr->scale_radiance(0.85);  
	
	SphereMaterials* sphere_materials_ptr = new SphereMaterials;
	sphere_materials_ptr->set_num_horizontal(16);
	sphere_materials_ptr->set_num_vertical(8);
	sphere_materials_ptr->set_line_width(0.04);
	sphere_materials_ptr->set_checker1_material(reflective_ptr);
	sphere_materials_ptr->set_checker2_material(reflective_ptr);
	sphere_materials_ptr->set_line_material(emissive_ptr);
	
	
	Sphere* sphere_ptr3 = new Sphere;
	sphere_ptr3->set_material(reflective_ptr);
	sphere_ptr3->set_material(sphere_materials_ptr);

	Instance* sphere_ptr4 = new Instance(sphere_ptr3);
	sphere_ptr4->scale(3.0);
	sphere_ptr4->translate(0.0, 4.5, 0.0);
	add_object(sphere_ptr4);
	
	
	// rectangle
	
	Checker3D* checker_ptr2 = new Checker3D;
	checker_ptr2->set_size(4.0);
	checker_ptr2->set_color1(0.5);  
	checker_ptr2->set_color2(white);	 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.35);
	sv_matte_ptr->set_cd(checker_ptr2);	
		
	Rectangle* rectangle_ptr = new Rectangle(Point3D(-20, -0.001, -100), Vector3D(0, 0, 120), Vector3D(40, 0, 0)); 
	rectangle_ptr->set_material(sv_matte_ptr);
	add_object(rectangle_ptr);
}


