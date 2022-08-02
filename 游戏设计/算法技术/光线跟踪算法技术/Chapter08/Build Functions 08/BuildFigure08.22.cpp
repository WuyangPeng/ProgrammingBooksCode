// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 8.22

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;	
		
//	pinhole_ptr->set_eye(0, 0, 10);       	// for Figure 8.22(a)
//	pinhole_ptr->set_view_distance(1687);
	
//	pinhole_ptr->set_eye(0, 0, 5);       	// for Figure 8.22(b)
//	pinhole_ptr->set_view_distance(750);
	
	pinhole_ptr->set_eye(0, 0, 2.5);       	// for Figure 8.22(c)
	pinhole_ptr->set_view_distance(280);
	
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(10, 50, 40);
	light_ptr->scale_radiance(3.0); 
	add_light(light_ptr);
	
	Phong* phong_ptr = new Phong;			
	phong_ptr->set_ka(0.25); 
	phong_ptr->set_kd(0.65); 
	phong_ptr->set_cd(white);   
	phong_ptr->set_ks(0.1); 
	phong_ptr->set_exp(25); 
	
	Point3D p0(-1.0);
	Point3D p1(1.0);
	float bevel_radius = 0.02;
	
	WireframeBox* box_ptr = new WireframeBox(p0, p1, bevel_radius);
	box_ptr->set_material(phong_ptr);
	add_object(box_ptr);	
}


