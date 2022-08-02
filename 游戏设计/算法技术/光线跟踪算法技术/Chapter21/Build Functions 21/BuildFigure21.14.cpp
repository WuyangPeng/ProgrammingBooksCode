// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.14
// This builds a thick ring that has different materials on some parts
// The ring is just a Compound object
// The parts are primitives that are constructed and added to the ring in the build function
// Before you can render this scene, you will have to have implemented an annulus and an open cylinder
// The ring is rendered after it has been transformed by nested instances
// This scene also includes a sphere and a ground plane for testing shadows

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(4, 3.25, 5);
	pinhole_ptr->set_lookat(0.85, 0.0, 0);
	pinhole_ptr->set_view_distance(900); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
		
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(20, 10, 15);
	light_ptr1->scale_radiance(2.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
			
	
	// ring parameters	
		
	Point3D centre(0);
	float y0 = -0.25;
	float y1 = 0.25;
	float inner_radius = 0.5;
	float outer_radius = 1.0;
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.3);    
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(0, 1, 1);  // cyan
	
	Annulus* bottom_ptr = new Annulus(Point3D(0, y0, 0), Normal(0, -1, 0), inner_radius, outer_radius); 
	bottom_ptr->set_material(matte_ptr1);
	
	Annulus* top_ptr = new Annulus(Point3D(0, y1, 0),  Normal(0, 1, 0), inner_radius, outer_radius); 
	top_ptr->set_material(matte_ptr1);
	
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.4);    
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(1, 1, 0);   // yellow
	
	OpenCylinder* outer_wall_ptr = new OpenCylinder(y0, y1, outer_radius); 
	outer_wall_ptr->set_material(matte_ptr2);
	
		
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.4);    
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(1, 1, 0);   // yellow
	
	OpenCylinder* inner_wall_ptr = new OpenCylinder(y0, y1, inner_radius); 
	inner_wall_ptr->set_material(matte_ptr3);
	
	
	// construct the ring as a compound object
	
	Compound* ring_ptr = new Compound;
	ring_ptr->add_object(bottom_ptr); 
	ring_ptr->add_object(top_ptr);
	ring_ptr->add_object(outer_wall_ptr);
	ring_ptr->add_object(inner_wall_ptr);
	
	// use nested instances for the transformed ring
	
	Instance* rotated_ring_ptr = new Instance(ring_ptr);
	rotated_ring_ptr->rotate_z(-45);
	
	Instance* translated_ring_ptr = new Instance(rotated_ring_ptr);
	translated_ring_ptr->translate(1, 0, 0);
	add_object(translated_ring_ptr);
	
	// sphere
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->set_ka(0.15);    
	matte_ptr4->set_kd(0.9);
	matte_ptr4->set_cd(1, 0.75, 0);
	
	Sphere* sphere_ptr = new Sphere(Point3D(2, 1, 0.5), 0.2);
	sphere_ptr->set_material(matte_ptr4);
	add_object(sphere_ptr);
	
	// ground plane
	
	Matte* matte_ptr5 = new Matte;			
	matte_ptr5->set_ka(0.15);    
	matte_ptr5->set_kd(0.75);
	matte_ptr5->set_cd(1.0);
	
	Plane* plane_ptr = new Plane(Point3D(0, -2, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr5);
	add_object(plane_ptr);
}

