// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 10.12

void 												
World::build(void) {
	int num_samples = 100;
	
	vp.set_hres(450);                                                               	  		
	vp.set_vres(300);
	vp.set_pixel_size(0.05);
	vp.set_samples(num_samples);
	vp.set_max_depth(1);
	
	tracer_ptr = new Whitted(this);

	background_color = white;
	
	ThinLens* thin_lens_ptr = new ThinLens;
	thin_lens_ptr->set_sampler(new MultiJittered(num_samples));

	Point3D eye(15, 25, 50); 
	Point3D lookat(0, 8, 0); 
	Vector3D direction(lookat - eye); 
	direction.normalize();
	float fd = 100;
		
	thin_lens_ptr->set_eye(15, 25, 50);  
	thin_lens_ptr->set_lookat(0, 8, 0);
	thin_lens_ptr->set_view_distance(30);
	thin_lens_ptr->set_focal_distance(100); 
	thin_lens_ptr->set_lens_radius(1);
	thin_lens_ptr->compute_uvw();     
	set_camera(thin_lens_ptr);
	

	// directional light 
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(1, 1, -0.5);      
	light_ptr->scale_radiance(4.0);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	

	Reflective* reflective_ptr = new Reflective;
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(0.2, 0.9, 0.75);
	
	Box* box_ptr = new Box(Point3D(-17, 0, -1), Point3D(13, 19, 0));
	box_ptr->set_material(reflective_ptr);
	add_object(box_ptr);
	
	
	// ground plane
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(8.0);
	checker_ptr->set_color1(0.25);  			// gray
	checker_ptr->set_color2(white);	 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.75);
	sv_matte_ptr->set_cd(checker_ptr);	

	Plane* plane_ptr1 = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr1->set_material(sv_matte_ptr);
	add_object(plane_ptr1);
	
	// focal plane plane
	
	Matte* matte_ptr = new Matte;
	matte_ptr->set_cd(1, 0, 0);
	matte_ptr->set_ka(0.5);
	matte_ptr->set_kd(0.5);
	
	Point3D point = eye + direction * fd;
	Normal normal = -direction;
	
	Plane* plane_ptr2 = new Plane(point, normal); 
	plane_ptr2->set_material(matte_ptr);
	add_object(plane_ptr2);
		
}



