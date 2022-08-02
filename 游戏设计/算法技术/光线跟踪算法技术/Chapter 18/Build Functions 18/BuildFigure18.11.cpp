// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 18.11

void 												
World::build(void) {
	int num_samples = 100;
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
		
	tracer_ptr = new AreaLighting(this);	
		
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->set_sampler(new MultiJittered(num_samples));
	ambient_occluder_ptr->set_min_amount(0.5);
	set_ambient_light(ambient_occluder_ptr);

			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 45, 100);  
	pinhole_ptr->set_lookat(-10, 40, 0);  
	pinhole_ptr->set_view_distance(400);  
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);

	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(0.90);
	emissive_ptr->set_ce(white);   	
		
	ConcaveSphere* sphere_ptr = new ConcaveSphere;
	sphere_ptr->set_radius(1000000.0);
	sphere_ptr->set_material(emissive_ptr);
	sphere_ptr->set_shadows(false);
	add_object(sphere_ptr);
	
	EnvironmentLight* environment_light_ptr = new EnvironmentLight;
	environment_light_ptr->set_material(emissive_ptr);
	environment_light_ptr->set_sampler(new MultiJittered(num_samples));
	environment_light_ptr->set_shadows(true);
	add_light(environment_light_ptr);
	
	
	float ka = 0.2;  		// commom ambient reflection coefficient
	float ks = 1.0;  		// commom specular reflection coefficient
	float exp = 10.0;   	// for Figure 18.11(a)
//	float exp = 50.0;   	// for Figure 18.11(b)
//	float exp = 200.0;   	// for Figure 18.11(c)
	RGBColour cs(1, 0, 0); 	// common specular color
	
	// large sphere
	
	Phong* phong_ptr1 = new Phong;			
	phong_ptr1->set_ka(ka); 
	phong_ptr1->set_kd(0.6);
	phong_ptr1->set_cd(0.75);
	phong_ptr1->set_ks(ks);
	phong_ptr1->set_exp(exp);
	phong_ptr1->set_cs(cs);
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	sphere_ptr1->set_material(phong_ptr1);
	add_object(sphere_ptr1);
	
	
	// small sphere
		
	Phong* phong_ptr2 = new Phong;			
	phong_ptr2->set_ka(ka); 
	phong_ptr2->set_kd(0.5);
	phong_ptr2->set_cd(0.95);
	phong_ptr2->set_ks(ks);
	phong_ptr2->set_exp(exp);
	phong_ptr2->set_cs(cs);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->set_material(phong_ptr2);
	add_object(sphere_ptr2);
	
	
	// medium sphere
	
	Phong* phong_ptr3 = new Phong;			
	phong_ptr3->set_ka(ka); 
	phong_ptr3->set_kd(0.5);
	phong_ptr3->set_cd(0.75);
	phong_ptr3->set_ks(ks);
	phong_ptr3->set_exp(exp);
	phong_ptr3->set_cs(cs);
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->set_material(phong_ptr3);
	add_object(sphere_ptr3);
	
	
	// cylinder
	
	Phong* phong_ptr4 = new Phong;			
	phong_ptr4->set_ka(ka); 
	phong_ptr4->set_kd(0.5);
	phong_ptr4->set_cd(0.60);
	phong_ptr4->set_ks(ks);
	phong_ptr4->set_exp(exp);
	phong_ptr4->set_cs(cs);
	
	float bottom 	= 0.0;
	float top 		= 85; 
	float radius	= 22;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(phong_ptr4);
	add_object(cylinder_ptr);

	
	// box
	
	Phong* phong_ptr5 = new Phong;			
	phong_ptr5->set_ka(ka); 
	phong_ptr5->set_kd(0.5);
	phong_ptr5->set_cd(0.95);
	phong_ptr5->set_ks(ks);
	phong_ptr5->set_exp(exp);
	phong_ptr5->set_cs(cs);
	
	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->set_material(phong_ptr5);
	add_object(box_ptr);
	
				
	// ground plane
		
	Matte* matte_ptr6 = new Matte;			
	matte_ptr6->set_ka(0.15); 
	matte_ptr6->set_kd(0.5);	
	matte_ptr6->set_cd(0.7);    
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr6);
	add_object(plane_ptr);
}


