// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 24.41(a).

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);      
	vp.set_vres(600);
	vp.set_pixel_size(0.004);     
	vp.set_max_depth(1);
	vp.set_samples(num_samples);
	
	background_color = RGBColor(0.0, 0.25, 0.0);   // dark green
	
	tracer_ptr = new Whitted(this);	
	
	Orthographic* ortho_ptr = new Orthographic;
	ortho_ptr->set_eye(0, 10, 0);  
	ortho_ptr->set_lookat(0.0);
	ortho_ptr->compute_uvw();     
	set_camera(ortho_ptr);
	 
		
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 1, 0);
	light_ptr->scale_radiance(2.5);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// sphere
		
	Reflective* reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.0); 
	reflective_ptr->set_cd(black);
	reflective_ptr->set_ks(0.0);
	reflective_ptr->set_exp(1.0);			
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(1.0, 1.0, 0);  // yellow
	
	Sphere* sphere_ptr = new Sphere(Point3D(0.0, 5.0, 0.0), 1);
	sphere_ptr->set_material(reflective_ptr);
	add_object(sphere_ptr);
	
	
	// plane with checker
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(2);
	checker_ptr->set_color1(0.0);
	checker_ptr->set_color2(1.0);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.33);
	sv_matte_ptr->set_kd(0.75);
	sv_matte_ptr->set_cd(checker_ptr);

	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr);
	plane_ptr->set_shadows(false);
	add_object(plane_ptr);	
}



