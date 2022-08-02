// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.7

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(280);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 15, 50);
	pinhole_ptr->set_lookat(0, 0.75, 0);
	pinhole_ptr->set_view_distance(4000); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
		
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(10, 15, 20);
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
		
	Phong* phong_ptr = new Phong;			
	phong_ptr->set_ka(0.3);    
	phong_ptr->set_kd(0.75);
	phong_ptr->set_cd(0.7, 0.5, 0);		// orange
	phong_ptr->set_ks(0.2);
	phong_ptr->set_exp(3);
	
	float bevel_radius = 0.05;  // for all objects
		
	// cylinder
	
	float y0  = -0.75; 
	float y1  = 1.25; 
	float radius = 1.0;
	
	Instance* cylinder_ptr = new Instance(new BeveledCylinder(y0, y1, radius, bevel_radius));
	cylinder_ptr->translate(-2.75, 0, 0);
	cylinder_ptr->set_material(phong_ptr);
	add_object(cylinder_ptr);

	// thick ring
	
	y0 = -0.125;
	y1 = 0.125;
	float inner_radius = 0.75;
	float outer_radius = 1.6;
	
	Instance* ring_ptr = new Instance(new BeveledRing(y0, y1, inner_radius, outer_radius, bevel_radius));
	ring_ptr->rotate_x(90);
	ring_ptr->rotate_y(-30);
	ring_ptr->translate(0.0, 0.85, 0.5);
	ring_ptr->set_material(phong_ptr);
	add_object(ring_ptr);
		
	// box
	// the untransformed box is centered on the origin
	
	Point3D p0(-0.75, -1.125, -0.75);
	Point3D p1(0.75, 1.125, 0.75);
	
	Instance* box_ptr = new Instance(new BeveledBox(p0, p1, bevel_radius));
	box_ptr->rotate_y(-10);
	box_ptr->translate(2.5, 0.38, -1);
	box_ptr->set_material(phong_ptr);
	add_object(box_ptr);
	
	// ground plane
	
	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.5);
	matte_ptr->set_kd(0.85);
	matte_ptr->set_cd(0.25);
	
	Plane* plane_ptr = new Plane(Point3D(0, -0.75, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);
}

