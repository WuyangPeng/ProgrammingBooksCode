// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.5(b)

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(1);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(100, 0, 100);   
	pinhole_ptr->set_lookat(0, 1, 0); 	 
	pinhole_ptr->set_view_distance(8000);	
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(50, 50, 1);
	light_ptr->scale_radiance(3.0);   
	add_light(light_ptr);
	
	Phong* phong_ptr = new Phong;			
	phong_ptr->set_cd(0.75);  
	phong_ptr->set_ka(0.25); 
	phong_ptr->set_kd(0.8);
	phong_ptr->set_ks(0.15); 
	phong_ptr->set_exp(50.0);  
	
	Instance* ellipsoid_ptr = new Instance(new Sphere);
	ellipsoid_ptr->set_material(phong_ptr);
	ellipsoid_ptr->scale(2, 3, 1);
	ellipsoid_ptr->rotate_x(-45);
	ellipsoid_ptr->translate(0, 1, 0);
	add_object(ellipsoid_ptr);
}	
	
	
