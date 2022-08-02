// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 14.7

void 												
World::build(void){
	int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
			
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	float a = 0.75;
	background_color = RGBColor(0.0, 0.3 * a, 0.25 * a);  // torquise
			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(7.5, 4, 10); 
	pinhole_ptr->set_lookat(-1, 3.7, 0);  
	pinhole_ptr->set_view_distance(340);		
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(15, 15, 2.5); 
	light_ptr->scale_radiance(2.0);	
	add_light(light_ptr);
		
		
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0.75, 0.75, 0);    	// dark yellow
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.45); 
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(0.75, 0.25, 0);  	 // orange
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.4); 
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(1, 0.5, 1);  		// mauve
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->set_ka(ka);
	matte_ptr4->set_ka(0.15);
	matte_ptr4->set_kd(0.5);
	matte_ptr4->set_cd(0.75, 1.0, 0.75);   	// light green
	
	Matte* matte_ptr5 = new Matte;			
	matte_ptr5->set_ka(0.20); 
	matte_ptr5->set_kd(0.97);	
	matte_ptr5->set_cd(white);  
	
	
	
	// spheres
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(3.85, 2.3, -2.55), 2.3);
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(-0.7, 1, 4.2), 2);
	sphere_ptr2->set_material(matte_ptr2);     
	add_object(sphere_ptr2);

	// cylinder 
	
	float bottom 	= 0.0;
	float top 		= 8.5;   
	float radius	= 2.2;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(matte_ptr3);
	add_object(cylinder_ptr);
	
	// box
		
	Box* box_ptr = new Box(Point3D(-3.5, 0, -11), Point3D(-2.5, 6, 6.5));
	box_ptr->set_material(matte_ptr4);
	add_object(box_ptr);
	
	// ground plane
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr5);
	add_object(plane_ptr);
}


