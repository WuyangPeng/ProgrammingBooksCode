// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 8.16
// The sphere, box, and triangle also appear in Figures 3.1, 3.2, 3.14, 3.15, 3,16, 3.17
// 8.14, 8.19, 9.1, 9.9, and 9.11

void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(400);			
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	background_color = black;
	tracer_ptr = new RayCast(this);
	
	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(0, 0, 250);
	camera_ptr->set_lookat(0);    
	camera_ptr->set_view_distance(200);  	// for Figure 8.16(a)	
//	camera_ptr->set_view_distance(450);  	// for Figure 8.16(b)		
//	camera_ptr->set_view_distance(1000);  	// for Figure 8.16(c)
	camera_ptr->compute_uvw();		  
	set_camera(camera_ptr);
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(50, 150, 200); 
	light_ptr1->scale_radiance(6.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	
	// sphere
	
	Phong* phong_ptr1 = new Phong;			
	phong_ptr1->set_ka(0.5); 
	phong_ptr1->set_kd(0.4);
	phong_ptr1->set_cd(0.5, 0.6, 0);  	// green
	phong_ptr1->set_ks(0.05); 
	phong_ptr1->set_exp(25); 	
	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(-45, 45, 40), 50); 
	sphere_ptr1->set_material(phong_ptr1);
	add_object(sphere_ptr1);
	
	
	// box
	
	Matte* matte_ptr = new Matte;				
	matte_ptr->set_ka(0.4); 
	matte_ptr->set_kd(0.3);
	matte_ptr->set_cd(0.8, 0.5, 0);  	// orange
	
	Box* box_ptr1 = new Box(Point3D(20, -101, -100), Point3D(90, 100, 20));
	box_ptr1->set_material(matte_ptr);
	add_object(box_ptr1);

	
	// triangle
	
	Phong*	phong_ptr2 = new Phong;			
	phong_ptr2->set_ka(0.25); 
	phong_ptr2->set_kd(0.5); 
	phong_ptr2->set_cd(0, 0.5, 0.5);     // cyan
	phong_ptr2->set_ks(0.05); 
	phong_ptr2->set_exp(50); 

	Triangle* triangle_ptr1 = new Triangle(Point3D(-110, -85, 80), Point3D(120, 10, 20), Point3D(-40, 50, -30));
	triangle_ptr1->set_material(phong_ptr2);     
	add_object(triangle_ptr1);
	
}




