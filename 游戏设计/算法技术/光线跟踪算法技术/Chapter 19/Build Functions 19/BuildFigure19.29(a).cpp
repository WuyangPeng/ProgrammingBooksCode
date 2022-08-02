// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This tests the solid cylinder built as a compound object

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 5, 10);
	pinhole_ptr->set_lookat(0);	
	pinhole_ptr->set_view_distance(1200);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(10, 13, 20);
	light_ptr->scale_radiance(3.0); 
	light_ptr->set_shadows(true);
	add_light(light_ptr);	

	Matte* matte_ptr1 = new Matte;		
	matte_ptr1->set_ka(0.3);    
	matte_ptr1->set_kd(0.6);
	matte_ptr1->set_cd(0, 1, 1);   // cyan
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.3);    
	matte_ptr2->set_kd(0.6);
	matte_ptr2->set_cd(1, 1, 0);  // yellow
	
	float bottom = -1.0;
	float top = 1.0;
	float radius = 1.0;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_bottom_material(matte_ptr1); 	// cyan
	cylinder_ptr->set_top_material(matte_ptr1); 	// cyan
	cylinder_ptr->set_wall_material(matte_ptr2); 	// yellow
	add_object(cylinder_ptr);
	
	
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.25);    
	matte_ptr3->set_kd(1.0);
	matte_ptr3->set_cd(white);
	
	Plane* plane_ptr = new Plane(Point3D(0, -1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr3);
	add_object(plane_ptr);
}


