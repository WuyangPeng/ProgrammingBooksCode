// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 14.24

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);	
				
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 25, 100);  
	pinhole_ptr->set_lookat(0);   
	pinhole_ptr->set_view_distance(6500);	 
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(200, 250, 300);  
//	light_ptr->set_color(white);  			// for Figure 14.24(a)
	light_ptr->set_color(0, 0, 1);  		// for Figure 14.24(b)
	light_ptr->scale_radiance(3.0);			
	light_ptr->set_shadows(true);    // see Chapter 16
	add_light(light_ptr);
	
	
	// four spheres centered on the x axis
	
	float radius = 1.0;
	float gap = 0.2;	 // gap between spheres
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.0); 
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(1, 0, 0);		// red
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(-3.0 * radius - 1.5 * gap, 0.0, 0.0), radius);
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);
	
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.0); 
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(1, 0.5, 0);		// orange
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(-radius - 0.5 * gap, 0.0, 0.0), radius);
	sphere_ptr2->set_material(matte_ptr2);
	add_object(sphere_ptr2);
	
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.0); 
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(1, 1, 0);		// yellow
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(radius + 0.5 * gap, 0.0, 0.0), radius);
	sphere_ptr3->set_material(matte_ptr3);
	add_object(sphere_ptr3);
	
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->set_ka(0.0); 
	matte_ptr4->set_kd(0.75);
	matte_ptr4->set_cd(0, 1, 0);		// green
	
	Sphere* sphere_ptr4 = new Sphere(Point3D(3.0 * radius + 1.5 * gap, 0.0, 0.0), radius);
	sphere_ptr4->set_material(matte_ptr4);
	add_object(sphere_ptr4);
		
	
	// ground plane
	
	Matte* matte_ptr5 = new Matte;			
	matte_ptr5->set_ka(0.25); 
	matte_ptr5->set_kd(0.5);	
	matte_ptr5->set_cd(1.0);    
	
	Plane* plane_ptr = new Plane(Point3D(0, -1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr5);
	add_object(plane_ptr);
}


