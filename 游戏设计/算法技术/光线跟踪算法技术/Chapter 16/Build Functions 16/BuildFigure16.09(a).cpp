// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 16.9

// This is the same scene  as in Figure 16.1 exept that:
// (1) it's rendered at 300 x 200 pixels to make the individual pixels more visible
// (2) it's rendered with one sample per pixel
// (3) kEpsilon = 0.0 in the Box, Plane, SolidCylinder, Sphere, and Triangle hit and
// shodow_hit functions


void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(300);	  		
	vp.set_vres(200);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
			
	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(2, 2.5, 15);
	camera_ptr->set_lookat(0 + 3, 2.5, 0);
	camera_ptr->set_view_distance(700);    
	camera_ptr->compute_uvw(); 
	set_camera(camera_ptr);
	
	Directional* light_ptr1 = new Directional();
	light_ptr1->set_direction(200, 150, 125); 
	light_ptr1->scale_radiance(4.0);
//	light_ptr1->set_shadows(true);				// for Figure 16.1(b)
	add_light(light_ptr1);
		
	PointLight* light_ptr2 = new PointLight();
	light_ptr2->set_location(-12, 15, 30); 
	light_ptr2->scale_radiance(4.0);
//	light_ptr2->set_shadows(true);				// for Figure 16.1(b)
	add_light(light_ptr2);
		
	// sphere
	
	Matte* matte_ptr1 = new Matte();			
	matte_ptr1->set_ka(0.3); 
	matte_ptr1->set_kd(0.3);
	matte_ptr1->set_cd(0.5, 0.6, 0); 
	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0.0, 2.4, 0), 1.5); 
	sphere_ptr1->set_material(matte_ptr1);
	add_object(sphere_ptr1);	
	
	// box
	
	Matte* matte_ptr2 = new Matte();			
	matte_ptr2->set_ka(0.2); 
	matte_ptr2->set_kd(0.3);
	matte_ptr2->set_cd(0.8,0.5,0);
							
	Box* box_ptr1 = new Box(Point3D(5.4, -0.5, -3), Point3D(7.5, 4.75, 0.60));
	box_ptr1->set_material(matte_ptr2);
	add_object(box_ptr1);
		
	// triangle
	
	Matte* matte_ptr3 = new Matte();			
	matte_ptr3->set_ka(0.35); 
	matte_ptr3->set_kd(0.50);
	matte_ptr3->set_cd(0, 0.5, 0.5);      // cyan

	Triangle* triangle_ptr1 = new Triangle(	Point3D(1.5, -0.5, 1.8), 		// front
											Point3D(7.5, -0.5, -9.00), 		// back
											Point3D(2.35, 5.8, 1.4));		// top									
	triangle_ptr1->set_material(matte_ptr3);        
	add_object(triangle_ptr1);
		
	// cylinder

	float bottom 	= -0.5;
	float top 		= 1.0;
	float radius 	= 1.0;

	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(matte_ptr2);
	add_object(cylinder_ptr);

	// ground plane

	Matte* matte_ptr4 = new Matte();			
	matte_ptr4->set_ka(0.1); 
	matte_ptr4->set_kd(0.2);
	matte_ptr4->set_cd(white);
	
	Plane* plane_ptr = new Plane(Point3D(0, -0.5, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr4);
	add_object(plane_ptr);
}



