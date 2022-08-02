// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 26.9(b)

void 												
World::build(void) {
	int num_samples = 5041;
	
	vp.set_hres(600);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples); 
	vp.set_max_depth(5);
		
	tracer_ptr = new PathTrace(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(5, 15, 20);			
	pinhole_ptr->set_lookat(-1, 1, 0);
	pinhole_ptr->set_view_distance(1500);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
			
	
	// emissive sphere
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->set_ce(0.75, 1, 0.75);
	emissive_ptr->scale_radiance(30.0);   
		
	Sphere* sphere_ptr = new Sphere(Point3D(-2, 7, 6), 1); 
	sphere_ptr->set_material(emissive_ptr);
	sphere_ptr->set_sampler(new MultiJittered(num_samples));
	add_object(sphere_ptr);
		
	
	// reflective open half cylinder
	
	Reflective* reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.4); 
	reflective_ptr->set_ks(0.0);      
	reflective_ptr->set_exp(1.0);
	reflective_ptr->set_kr(0.95); 
	reflective_ptr->set_cr(1.0, 0.5, 0.25);  // orange 
	
	double y0 		= -1.0;
	double y1 		= 3.0;
	double radius 	= 3.0;
	double phi_min 	= 90.0;
	double phi_max 	= 270.0;
	
	ConcavePartCylinder* cylinder_ptr = new ConcavePartCylinder(y0, y1, radius, phi_min, phi_max); 
	cylinder_ptr->set_material(reflective_ptr);
	add_object(cylinder_ptr);	
	
	
	// plane

	Matte* matte_ptr = new Matte;			
	matte_ptr->set_ka(0.0);		
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(1);
	matte_ptr->set_sampler(new MultiJittered(num_samples));
	
	Plane* plane_ptr = new Plane(Point3D(0, -1.0, 0), Normal(0, 1, 0)); 	
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);
}


