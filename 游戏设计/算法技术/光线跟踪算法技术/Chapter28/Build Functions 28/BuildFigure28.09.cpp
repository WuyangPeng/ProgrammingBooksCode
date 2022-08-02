// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.9

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(6);		
	
	background_color = white;
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
	
		
	Pinhole* pinhole_ptr = new Pinhole;	
	pinhole_ptr->set_eye(2.8125, 0, 1000);   
	pinhole_ptr->set_lookat(2.8125, 0, 0);
	pinhole_ptr->set_view_distance(50000.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ka(0.0);
	dielectric_ptr->set_kd(0.0); 
	dielectric_ptr->set_ks(0.0);    
	dielectric_ptr->set_exp(2000);
	dielectric_ptr->set_eta_in(1.5);   
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(0.65, 0.45, 0);   // orange
	dielectric_ptr->set_cf_out(1.0);
	
	
	// a row of spheres
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(0), 3.0);
	sphere_ptr1->set_material(dielectric_ptr);
	add_object(sphere_ptr1);
	
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(4.5, 0, 0), 1.5);
	sphere_ptr2->set_material(dielectric_ptr);
	add_object(sphere_ptr2);
	
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(6.75, 0, 0), 0.75);
	sphere_ptr3->set_material(dielectric_ptr);
	add_object(sphere_ptr3);
	
	Sphere* sphere_ptr4 = new Sphere(Point3D(7.875, 0, 0), 0.375);
	sphere_ptr4->set_material(dielectric_ptr);
	add_object(sphere_ptr4);
	
	Sphere* sphere_ptr5 = new Sphere(Point3D(8.4375, 0, 0), 0.1875);
	sphere_ptr5->set_material(dielectric_ptr);
	add_object(sphere_ptr5);
}


