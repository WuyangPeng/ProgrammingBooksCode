// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.50

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(15);
	
	tracer_ptr = new Whitted(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(1, 0.5, 4);      
	pinhole_ptr->set_lookat(-3, -10, 0); 	   
	pinhole_ptr->set_view_distance(200.0);  
	pinhole_ptr->set_exposure_time(0.17);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	// transparent sphere
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_eta_in(2.42);		// diamond
	dielectric_ptr->set_eta_out(1.0);		// air
	dielectric_ptr->set_cf_in(white);
	dielectric_ptr->set_cf_out(white); 
		
	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0), 4.0);
	sphere_ptr1->set_material(dielectric_ptr);
		
	
	// scale the sphere into an ellipsoid
	
	Instance* ellipsoid_ptr = new Instance(sphere_ptr1);
	ellipsoid_ptr->scale(1.0, 0.75, 2.0);
	add_object(ellipsoid_ptr);
		
	
	// emissive concave sphere with checkers
	
	RGBColor c1(0, 0.25, 0.35);
	RGBColor c2(1, 1, 0.5);
	
	SphereChecker* checker_ptr = new SphereChecker;
	checker_ptr->set_num_horizontal(12);  
	checker_ptr->set_num_vertical(6);    
	checker_ptr->set_horizontal_line_width(0.0);
	checker_ptr->set_vertical_line_width(0.0);
	checker_ptr->set_color1(c1);   
	checker_ptr->set_color2(c2); 
	checker_ptr->set_line_color(black);  
		
	SV_Emissive* sv_emissive_ptr = new SV_Emissive;
	sv_emissive_ptr->scale_radiance(1.0);
	sv_emissive_ptr->set_ce(checker_ptr);

	ConcaveSphere* sphere_ptr2 = new ConcaveSphere;  // you will have to implement this
	sphere_ptr2->set_material(sv_emissive_ptr);		 // or use a default ConcavePartSphere
	
	Instance* sphere_ptr3 = new Instance(sphere_ptr2);
	sphere_ptr3->scale(100.0);
	add_object(sphere_ptr3);
}


