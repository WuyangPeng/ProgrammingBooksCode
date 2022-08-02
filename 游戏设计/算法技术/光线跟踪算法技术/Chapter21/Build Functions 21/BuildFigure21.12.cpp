// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.12

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(350);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 15.75, 50);
	pinhole_ptr->set_lookat(0, 2, 0);	
	pinhole_ptr->set_view_distance(3500); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);

	Directional* light_ptr = new Directional;
	light_ptr->set_direction(10, 15, 20);
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
		
	Phong* phong_ptr = new Phong;			
	phong_ptr->set_ka(0.3);    
	phong_ptr->set_kd(0.75);
	phong_ptr->set_cd(0.7, 0.5, 0);		// orange
	phong_ptr->set_ks(0.15);
	phong_ptr->set_exp(3.0);
	
	
	// commmon cylinder parameters
	
	float radius 		= 1.0;
	float bevel_radius 	= 0.25;
		
	// short cylinder
	
	float y0 = 0.0;
	float y1 = 2.0;
	
	Instance* cylinder_ptr1 = new Instance(new BeveledCylinder(y0, y1, radius, bevel_radius));
	cylinder_ptr1->translate(-2.75, 0, 0);
	cylinder_ptr1->set_material(phong_ptr);
	add_object(cylinder_ptr1);
	
	// tall cylinder
	
	y0 = 0.0;
	y1 = 4.0;
	
	BeveledCylinder* cylinder_ptr2 = new BeveledCylinder(y0, y1, radius, bevel_radius);
	cylinder_ptr2->set_material(phong_ptr);
	add_object(cylinder_ptr2);
	
	// scaled cylinder
	
	y0 = 0.0;
	y1 = 2.0;
	
	Instance* cylinder_ptr3 = new Instance(new BeveledCylinder(y0, y1, radius, bevel_radius));
	cylinder_ptr3->scale(1, 2, 1);
	cylinder_ptr3->translate(2.75, 0, 0);
	cylinder_ptr3->set_material(phong_ptr);
	add_object(cylinder_ptr3);

	// ground plane
	
	Matte* matte_ptr = new Matte;
	matte_ptr->set_cd(1);
	matte_ptr->set_ka(0.25);
	matte_ptr->set_kd(1);
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);
}

