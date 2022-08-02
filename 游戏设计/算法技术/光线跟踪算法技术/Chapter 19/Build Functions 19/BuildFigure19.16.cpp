// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 19.16

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);	
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* camera = new Pinhole;
	camera->set_eye(5, 25, 20); 
	camera->set_lookat(0, 0, 0); 
	camera->set_view_distance(1500); 
	camera->compute_uvw();     
	set_camera(camera); 

	background_color = black;
		
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(200, 75, 100);
	light_ptr2->scale_radiance(4.0);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(0.25);
	phong_ptr2->set_kd(0.5);
	phong_ptr2->set_cd(1, 1, 0.45);  // lemon
	phong_ptr2->set_ks(0.05);
	phong_ptr2->set_exp(5);
	
	float a = 2.0;	 	// for all parts
	float b = 0.15;		// for Figure 19.16(a)
//	float b = 0.5;	   	// for Figure 19.16(b)  default torus
//	float b = 2;      	// for Figure 19.16(c)
																
	Torus* torus_ptr = new Torus(a, b);												
	torus_ptr->set_material(phong_ptr2);
	add_object(torus_ptr);
	
	
	// ground plane with checker:
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.0); 
	checker_ptr->set_color1(0.8);  
	checker_ptr->set_color2(1);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.30);
	sv_matte_ptr->set_kd(0.6);  
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -2, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);
}


