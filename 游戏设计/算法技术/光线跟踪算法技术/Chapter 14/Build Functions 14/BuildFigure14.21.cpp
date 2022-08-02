// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 14.21

void 												
World::build(void) {

	int num_samples = 16;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples); 
	
	tracer_ptr = new RayCast(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 500);
	pinhole_ptr->set_lookat(-5, 0, 0); 
	pinhole_ptr->set_vpd(850.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(100, 50, 150);
	light_ptr2->scale_radiance(3.0); 
	add_light(light_ptr2);

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);	
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(1, 1, 0);	  				// yellow	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(10, -5, 0), 27); 
	sphere_ptr1->set_material(matte_ptr1);	   							
	add_object(sphere_ptr1);
	
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.15);	
	matte_ptr2->set_kd(0.85);
	matte_ptr2->set_cd(0.71, 0.40, 0.16);   		// brown
	Sphere*	sphere_ptr2 = new Sphere(Point3D(-25, 10, -35), 27); 			
	sphere_ptr2->set_material(matte_ptr2);							
	add_object(sphere_ptr2);
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15);	
	matte_ptr3->set_kd(0.5);
	matte_ptr3->set_cd(0, 0.4, 0.2);				// dark green
	Plane* plane_ptr = new Plane(Point3D(0, 0, -50), Normal(0, 0, 1)); 
	plane_ptr->set_material(matte_ptr3);								
	add_object(plane_ptr);
}
