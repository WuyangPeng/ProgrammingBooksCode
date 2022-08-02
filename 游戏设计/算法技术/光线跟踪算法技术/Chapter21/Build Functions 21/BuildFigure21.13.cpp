// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.13
// For best effect, this needs to be rendered with one sample per pixel

void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 15, 50);
	pinhole_ptr->set_lookat(-2.75, 0.25, 0);
	pinhole_ptr->set_view_distance(7000); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
		
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(10, 15, 20);
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
		
	Phong* phong_ptr = new Phong;			
	phong_ptr->set_ka(0.3);    
	phong_ptr->set_kd(1.0);
	phong_ptr->set_cd(0.7, 0.5, 0);		// orange
	phong_ptr->set_ks(0.4);
	phong_ptr->set_kd(0.75);
	phong_ptr->set_ks(0.2);
	phong_ptr->set_exp(3.0);
			
	// cylinder
	
	float y0 = -0.75;
	float y1 = 1.25;
	float radius = 1.0;
	float bevel_radius = 1.0;
		
	Instance* cylinder_ptr = new Instance(new BeveledCylinder(y0, y1, radius, bevel_radius));
	cylinder_ptr->translate(-2.75, 0.0, 0.0);
	cylinder_ptr->set_material(phong_ptr);
	add_object(cylinder_ptr);
	
	// ground plane
	
	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.5);
	matte_ptr->set_kd(0.85);
	matte_ptr->set_cd(0.25);
	
	Plane* plane_ptr = new Plane(Point3D(0, -0.75, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);
}

