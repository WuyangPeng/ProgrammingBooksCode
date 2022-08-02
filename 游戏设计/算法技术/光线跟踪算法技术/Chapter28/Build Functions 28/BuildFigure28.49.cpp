// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.49

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(350);
	vp.set_samples(num_samples);	
	vp.set_max_depth(6);		
	
	background_color = white;
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	tracer_ptr = new Whitted(this);
	
	Pinhole* pinhole_ptr = new Pinhole;	
	pinhole_ptr->set_eye(0, 0, 1000);    
	pinhole_ptr->set_lookat(0, 0, 0);
	pinhole_ptr->set_view_distance(35000.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_eta_in(1.5);   
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(0.9, 0.7, 0);   // orange
	dielectric_ptr->set_cf_out(1.0);

	Instance* sphere_ptr1 = new Instance(new Sphere);
	sphere_ptr1->set_material(dielectric_ptr);
	sphere_ptr1->scale(4.0);
	sphere_ptr1->translate(-4.2, 0.0, 0.0);
	add_object(sphere_ptr1);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(4.2, 0, 0), 4);
	sphere_ptr2->set_material(dielectric_ptr);
	add_object(sphere_ptr2);
}


