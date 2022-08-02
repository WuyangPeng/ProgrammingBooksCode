// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for the Chapter 25 page one image.

void 												
World::build(void) {
	int num_samples = 256;   // use 1 for testing!
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(10);
		
	tracer_ptr = new AreaLighting(this);	
		
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->set_sampler(new MultiJittered(num_samples));
	ambient_occluder_ptr->set_min_amount(0.5);
	set_ambient_light(ambient_occluder_ptr);

			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 45, 100);  
	pinhole_ptr->set_lookat(-10, 35, 0);  
	pinhole_ptr->set_view_distance(400);  
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
		
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(150, 250, -150);   
	light_ptr2->scale_radiance(1.5);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);


	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_ce(1.0, 1.0, 0.5); 	 // lemon
	emissive_ptr->scale_radiance(0.85); 
	
	
	EnvironmentLight* environment_light_ptr = new EnvironmentLight;
	environment_light_ptr->set_material(emissive_ptr);
	environment_light_ptr->set_sampler(new MultiJittered(num_samples));
	environment_light_ptr->set_shadows(true);
	add_light(environment_light_ptr);
	
	
	// large concave sphere for direct rendering of environment light
	
	ConcaveSphere* sphere_ptr = new ConcaveSphere;
	sphere_ptr->set_radius(1000000.0);
	sphere_ptr->set_material(emissive_ptr);
	sphere_ptr->set_shadows(false);
	add_object(sphere_ptr);
	
	
	// other objects
		
	// large sphere
	
	GlossyReflector* glossy_ptr1 = new GlossyReflector;
	glossy_ptr1->set_samples(num_samples, 100.0);			
	glossy_ptr1->set_ka(0.0); 
	glossy_ptr1->set_kd(0.0);
	glossy_ptr1->set_ks(0.3);
	glossy_ptr1->set_exp(100.0);
	glossy_ptr1->set_cd(1.0, 1.0, 0.3);	 // orange
	glossy_ptr1->set_kr(0.9);
	glossy_ptr1->set_exponent(100.0);
	glossy_ptr1->set_cr(1.0, 0.75, 0.5);  // orange
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	sphere_ptr1->set_material(glossy_ptr1);
	add_object(sphere_ptr1);
	
	
	// small sphere
		
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.4); 
	matte_ptr2->set_kd(0.4);
	matte_ptr2->set_cd(0.75, 0, 0);     // red
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->set_material(matte_ptr2);
	add_object(sphere_ptr2);
	
	
	// medium sphere
	
	Reflective* reflective_ptr = new Reflective;			
	reflective_ptr->set_cd(0.75);
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.0); 
	reflective_ptr->set_ks(0.0);
	reflective_ptr->set_exp(20);
	reflective_ptr->set_kr(0.9);
	reflective_ptr->set_cr(1.0, 0.75, 0.5);   // orange
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->set_material(reflective_ptr);
	add_object(sphere_ptr3);
	
	
	// cylinder

	GlossyReflector* glossy_ptr2 = new GlossyReflector;
	glossy_ptr2->set_samples(num_samples, 10.0);			
	glossy_ptr2->set_ka(0.0); 
	glossy_ptr2->set_kd(0.0);
	glossy_ptr2->set_ks(0.75);
	glossy_ptr2->set_cs(0.35, 0.75, 0.55);  // green
	glossy_ptr2->set_exp(10.0);
	glossy_ptr2->set_cd(1.0, 1.0, 0.3);
	glossy_ptr2->set_kr(0.9);
	glossy_ptr2->set_exponent(10.0);
	glossy_ptr2->set_cr(0.35, 0.75, 0.55);   // green
	
	double bottom 	= 0.0;
	double top 		= 85.0;
	double radius	= 22.0;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(glossy_ptr2);
	add_object(cylinder_ptr);

	
	// box

	GlossyReflector* glossy_ptr3 = new GlossyReflector;
	glossy_ptr3->set_samples(num_samples, 1000.0);			
	glossy_ptr3->set_ka(0.2); 
	glossy_ptr3->set_kd(0.3);
	glossy_ptr3->set_ks(0.0);
	glossy_ptr3->set_exp(1000.0);
	glossy_ptr3->set_cd(0.4, 0.5, 1.0);   // blue
	glossy_ptr3->set_kr(0.9);
	glossy_ptr3->set_exponent(1000.0);
	glossy_ptr3->set_cr(0.4, 0.5, 1.0);   // blue
	
	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->set_material(glossy_ptr3);
	add_object(box_ptr);
	
	
	// ground plane with checker
	
	// checker with stripes
	
	PlaneChecker* checker_ptr = new PlaneChecker;
	checker_ptr->set_size(20.0);		
	checker_ptr->set_outline_width(2.0);
	checker_ptr->set_color1(1.0, 0.75, 0.5);
	checker_ptr->set_color2(white);
	checker_ptr->set_outline_color(black); 
	
	// Using the following glossy reflector material with the exponent = 1.0, 
	// allows us to render color bleeding from the objects onto the plane.
	// You will have to write this material and the PlaneChecker material
	// as exercises.
	
	SV_GlossyReflector* sv_glossy_ptr = new SV_GlossyReflector;		
	sv_glossy_ptr->set_samples(num_samples, 1.0);			
	sv_glossy_ptr->set_ka(0.0);
	sv_glossy_ptr->set_kd(0.0);
	sv_glossy_ptr->set_ks(0.0);
	sv_glossy_ptr->set_cs(checker_ptr);
	sv_glossy_ptr->set_exp(1.0);
	sv_glossy_ptr->set_cd(checker_ptr);
	sv_glossy_ptr->set_kr(0.75); 
	sv_glossy_ptr->set_exponent(1.0);
	sv_glossy_ptr->set_cr(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_glossy_ptr);
	add_object(plane_ptr);
}


