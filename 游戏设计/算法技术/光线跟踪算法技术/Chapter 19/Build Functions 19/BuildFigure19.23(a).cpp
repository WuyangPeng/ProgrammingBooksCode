// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 19.23(a)

void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new FirstHit(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 5, 10);
	pinhole_ptr->set_lookat(0);	
	pinhole_ptr->set_view_distance(1200);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	// point light
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(10, 13, 20);
	light_ptr1->scale_radiance(3.0); 
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);	

	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_cd(1, 1, 0); // yellow
	matte_ptr1->set_ka(0.3);    
	matte_ptr1->set_kd(0.6);
	
	// solid cylinder
	// the following values for bottom, top, and radius can also be the default values
	// by setting them in the SolidCylinder default constructor
	
	float bottom = -1.0;
	float top = 1.0;
	float radius = 1.0;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(matte_ptr1);
	add_object(cylinder_ptr);
	
	// ground plane
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_cd(1);				
	matte_ptr2->set_ka(0.25);    
	matte_ptr2->set_kd(1.0);
	Plane* plane_ptr1 = new Plane(Point3D(0, -1, 0), Normal(0, 1, 0));
	plane_ptr1->set_material(matte_ptr2);
	add_object(plane_ptr1);
}


