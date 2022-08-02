// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 24.36
// This produces different reflections for parts (c) and (d),
// because I couldn't reproduce the original images in (c) and (d).
// The exact patterns aren't important. 
// It's more intructive to think about parts (a) and (b), and why there are 
// reflective patterns in (c) and (d).

void 												
World::build(void) {
	int num_samples = 9;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_pixel_size(0.00425);
	vp.set_max_depth(1);
	vp.set_samples(num_samples);
	
	background_color = RGBColor(0.0, 0.3, 0.25);
	
	tracer_ptr = new Whitted(this);
	
	
	Orthographic* orthographic_ptr = new Orthographic;
	orthographic_ptr->set_eye(1.5, 1000.0, 0.0);     
	orthographic_ptr->set_lookat(1.5, 0.0, 0.0);
	orthographic_ptr->compute_uvw();
	set_camera(orthographic_ptr);
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0.0, 1.0, 0.0);
	light_ptr->scale_radiance(2.5);
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	
		
	// cone
	
	Reflective*	reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.0);	
	reflective_ptr->set_kd(0.0);
	reflective_ptr->set_cd(0, 0, 0);
	reflective_ptr->set_ks(0.0);
	reflective_ptr->set_exp(1.0);
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(1.0, 0.8, 0.0);	// orange	
	
	Instance* cone_ptr = new Instance(new SolidCone);
	cone_ptr->set_material(reflective_ptr);
//	cone_ptr->scale(1.0, 0.9, 1.0);			// for Figure 24.36(a)
	cone_ptr->scale(1.0, 1.0, 1.0);			// for Figure 24.36(b)
//	cone_ptr->scale(1.0, 1.1, 1.0);			// for Figure 24.36(c)
//	cone_ptr->scale(1.0, 3.0, 1.0);			// for Figure 24.36(d)
	cone_ptr->translate(1.5, -1, 0);
	add_object(cone_ptr);
	
	// ground plane with checker
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(0.45);		
	checker_ptr->set_color1(white);   
	checker_ptr->set_color2(0.5);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(checker_ptr);

	Plane* plane_ptr1 = new Plane(Point3D(0, -1.01, 0), Normal(0, 1, 0));  // for jug
	plane_ptr1->set_material(sv_matte_ptr);
	add_object(plane_ptr1);
}

