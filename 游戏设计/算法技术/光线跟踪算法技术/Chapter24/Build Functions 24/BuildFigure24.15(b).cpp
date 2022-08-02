// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figures 24.15(b)
// The SphereTexture texture is part of Exercise 30.4, 
// but the code is included in the Code download

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


	// the camera is looking at the center of the reflective sphere

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-8, 20, 40);   
	pinhole_ptr->set_lookat(0, 4.5, 0);     
	pinhole_ptr->set_view_distance(2700);	
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
	
	Reflective* reflective_ptr = new Reflective;			
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.0); 
	reflective_ptr->set_cd(1.0);
	reflective_ptr->set_ks(0.15);
	reflective_ptr->set_exp(300.0);
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(1.0, 0.75, 0.25);  // orange
	
	Sphere* sphere_ptr3 = new Sphere;
	sphere_ptr3->set_material(reflective_ptr);

	// we are using a transformed generic sphere here, because it will
	// have a textured material in Figure 24.15(c) and Figure 24.16.

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


