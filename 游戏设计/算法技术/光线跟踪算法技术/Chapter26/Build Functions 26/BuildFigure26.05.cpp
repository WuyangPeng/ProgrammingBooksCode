// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 26.5

void 												
World::build(void) {
	int num_samples = 100;

	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new AreaLighting(this);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.0);
	set_ambient_light(ambient_ptr);	

			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 45, 100);  
	pinhole_ptr->set_lookat(-10, 40, 0);  
	pinhole_ptr->set_view_distance(400);  	
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_ce(white);  
	emissive_ptr->scale_radiance(1.5);   
							
	EnvironmentLight* environmentLight_ptr = new EnvironmentLight;
	environmentLight_ptr->set_material(emissive_ptr);
	environmentLight_ptr->set_sampler(new MultiJittered(num_samples));
	environmentLight_ptr->set_shadows(true);
	add_light(environmentLight_ptr);
	
	
	ConcaveSphere* sphere_ptr = new ConcaveSphere;		// centered on the origin
	sphere_ptr->set_radius(1000000.0);
	sphere_ptr->set_shadows(false);
	sphere_ptr->set_material(emissive_ptr);
	add_object(sphere_ptr);	
	
		
	float ka = 0.2;  // common ambient reflection coefficient	

		
	// large sphere

	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(ka); 
	matte_ptr1->set_kd(0.60);
	matte_ptr1->set_cd(white);
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20); 
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);
	
	
	// small sphere
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(ka); 
	matte_ptr2->set_kd(0.5);
	matte_ptr2->set_cd(0.85);				// gray
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->set_material(matte_ptr2);
	add_object(sphere_ptr2);
	
	
	// medium sphere
		
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(ka); 
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(0.73, 0.22, 0.0);    // orange
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->set_material(matte_ptr3);
	add_object(sphere_ptr3);
	
	
	// cylinder
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->set_ka(ka); 
	matte_ptr4->set_kd(0.75);
	matte_ptr4->set_cd(0.60);				// gray
			
	double bottom 	= 0.0;
	double top 		= 85.0;
	double radius	= 22.0;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(matte_ptr4);
	add_object(cylinder_ptr);

	
	// box
	
	MultiJittered* sampler_ptr5 = new MultiJittered(num_samples);
	
	Matte* matte_ptr5 = new Matte;			
	matte_ptr5->set_ka(ka); 
	matte_ptr5->set_kd(0.75);
	matte_ptr5->set_cd(0.95);				// gray
	
	Box* box_ptr = new Box(Point3D(-55, 0, -110), Point3D(-25, 60, 65));  // thicker
	box_ptr->set_material(matte_ptr5);
	add_object(box_ptr);
	
	
	// ground plane
			
	Matte* matte_ptr6 = new Matte;			
	matte_ptr6->set_ka(0.15); 
	matte_ptr6->set_kd(0.95);	
	matte_ptr6->set_cd(0.37, 0.43, 0.08);     // olive green
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr6);
	add_object(plane_ptr);
}


