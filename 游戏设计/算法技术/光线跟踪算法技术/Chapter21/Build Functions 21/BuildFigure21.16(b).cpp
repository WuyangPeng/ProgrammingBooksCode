// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.16(b)
// To render this scene, you will have to implement a round-rimmed bowl as described in 
// Exercise 21.7

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(1);
	
	tracer_ptr = new RayCast(this);
		
	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(1, 2, 5);       
	camera_ptr->set_lookat(0, -0.1, 0);
	camera_ptr->set_view_distance(700); 
	camera_ptr->compute_uvw();
	set_camera(camera_ptr);
		
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(20, 15, 15);    
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	
	// bowl
		
	Phong* phong_ptr = new Phong;				
	phong_ptr->set_ka(0.25);    
	phong_ptr->set_kd(0.5);
	phong_ptr->set_cd(0.53, 0.67, 0.34);	// yellow green	
	phong_ptr->set_ks(0.1);
	phong_ptr->set_exp(50);

	float inner_radius = 1.0;
	float outer_radius = 1.2;
	float wall_thickness = 0.2;
	float opening_angle = 120;  // in degrees
	
	RoundRimmedBowl* bowl_ptr = new RoundRimmedBowl(inner_radius, outer_radius, opening_angle);
	bowl_ptr->set_material(phong_ptr);
	add_object(bowl_ptr);
	
	
	// ground plane with checker
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1);		
	checker_ptr->set_color1(white);  
	checker_ptr->set_color2(0.75);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.35);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(checker_ptr);

	Plane* plane_ptr = new Plane(Point3D(0, -1.01, 0), Normal(0, 1, 0)); 
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);	
}

