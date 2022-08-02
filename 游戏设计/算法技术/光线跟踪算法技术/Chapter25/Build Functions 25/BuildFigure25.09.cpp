// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 25.9.

void 												
World::build(void) {
	int num_samples = 256;
	
	vp.set_hres(600);	  		
	vp.set_vres(200);
	vp.set_samples(num_samples);
	vp.set_max_depth(1);
	
	background_color = black;
	tracer_ptr = new AreaLighting(this);
	
	Ambient* ambient_ptr = new Ambient; 
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(-2, 300, 400);
	pinhole_ptr->set_lookat(-2, 8, 0);
	pinhole_ptr->set_view_distance(3500);
	pinhole_ptr->compute_uvw();  
	set_camera(pinhole_ptr);
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(20, 30, 40); 
	light_ptr->scale_radiance(4.0);
	light_ptr->set_shadows(false);
	add_light(light_ptr);

	// boxes
	
	float checker_size = 4.0;
	
	float exp1 = 100000.0;
	GlossyReflector* glossy_ptr1 = new GlossyReflector;
	glossy_ptr1->set_cd(0, 0.5, 0.25);
	glossy_ptr1->set_ka(0.2);
	glossy_ptr1->set_kd(0.3);	
	glossy_ptr1->set_ks(0.0);
	glossy_ptr1->set_exp(exp1);
	glossy_ptr1->set_kr(0.5);
	glossy_ptr1->set_sampler(new MultiJittered(num_samples), exp1);
		
	Box* box_ptr1 = new Box;
	box_ptr1->set_p0(-10.0 * checker_size, 0, -0.5);
	box_ptr1->set_p1(-6.0 * checker_size, 5 * checker_size, 0.0);
	box_ptr1->set_material(glossy_ptr1);
	add_object(box_ptr1);
	
	float exp2 = 10000.0;
	GlossyReflector* glossy_ptr2 = new GlossyReflector;
	glossy_ptr2->set_cd(0, 0.5, 0.25);
	glossy_ptr2->set_ka(0.2);
	glossy_ptr2->set_kd(0.3);	
	glossy_ptr2->set_ks(0.0);
	glossy_ptr2->set_exp(exp2);
	glossy_ptr2->set_kr(0.5);
	glossy_ptr2->set_sampler(new MultiJittered(num_samples), exp2);
	
	Box* box_ptr2 = new Box;
	box_ptr2->set_p0(-5.0 * checker_size, 0, -0.5);
	box_ptr2->set_p1(-checker_size, 5 * checker_size, 0.0);
	box_ptr2->set_material(glossy_ptr2);
	add_object(box_ptr2);
	
	float exp3 = 1000.0;
	GlossyReflector* glossy_ptr3 = new GlossyReflector;
	glossy_ptr3->set_cd(0, 0.5, 0.25);
	glossy_ptr3->set_ka(0.2);
	glossy_ptr3->set_kd(0.3);	
	glossy_ptr3->set_ks(0.0);
	glossy_ptr3->set_exp(exp3);
	glossy_ptr3->set_kr(0.5);
	glossy_ptr3->set_sampler(new MultiJittered(num_samples), exp3);
	
	Box* box_ptr3 = new Box;
	box_ptr3->set_p0(0, 0, -0.5);
	box_ptr3->set_p1(4 * checker_size, 5 * checker_size, 0.0);
	box_ptr3->set_material(glossy_ptr3);
	add_object(box_ptr3);
	
	float exp4 = 100.0;
	GlossyReflector* glossy_ptr4 = new GlossyReflector;
	glossy_ptr4->set_cd(0, 0.5, 0.25);
	glossy_ptr4->set_ka(0.2);
	glossy_ptr4->set_kd(0.3);	
	glossy_ptr4->set_ks(0.0);
	glossy_ptr4->set_exp(exp4);
	glossy_ptr4->set_kr(0.5);
	glossy_ptr4->set_sampler(new MultiJittered(num_samples), exp4);
	
	Box* box_ptr4 = new Box;
	box_ptr4->set_p0(5 * checker_size, 0, -0.5);
	box_ptr4->set_p1(9 * checker_size, 5 * checker_size, 0.0);
	box_ptr4->set_material(glossy_ptr4);
	add_object(box_ptr4);
	
	
	// vertical back plane
	
	Matte* matte_ptr = new Matte;			
	matte_ptr->set_ka(0.25);    
	matte_ptr->set_kd(0.25);
	matte_ptr->set_cd(white);
	
	Plane* plane_ptr1 = new Plane(Point3D(0, 0, -4), Normal(0, 0, 1)); 
	plane_ptr1->set_material(matte_ptr);
	add_object(plane_ptr1);
	
	
	// ground plane with checker
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(checker_size);
	checker_ptr->set_color1(black);
	checker_ptr->set_color2(white);
	 
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.8);  
	sv_matte_ptr->set_kd(0.4);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr2 = new Plane(Point3D(0, -0.01, 0), Normal(0, 1, 0)); 
	plane_ptr2->set_material(sv_matte_ptr);
	add_object(plane_ptr2);	
}


