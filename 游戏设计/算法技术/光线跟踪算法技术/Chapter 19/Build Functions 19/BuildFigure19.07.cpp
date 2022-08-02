// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 19.7
// Instances are covered in Chapter 21

void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(25, 200, 100);  
	pinhole_ptr->set_lookat(-0.5, 0, 0);  
	pinhole_ptr->set_view_distance(8000);	
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(1, 5, 0);
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	
	// yellow triangle
		
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.25); 
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(1, 1, 0);
	
	Triangle* triangle_ptr1 = new Triangle(Point3D(2, 0.5, 5), Point3D(2, 1.5, -5), Point3D(-1, 0, -4)); 
	triangle_ptr1->set_material(matte_ptr1);
	add_object(triangle_ptr1);
	
	
	// dark green triangle (transformed)
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.25); 
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(0.0, 0.5, 0.41);
	
	Instance* triangle_ptr2 = new Instance(new Triangle(Point3D(2, 1, 5), Point3D(2, 0.5, -5), Point3D(-1, -1, -4))); 
	triangle_ptr2->rotate_y(120);
	triangle_ptr2->set_material(matte_ptr2);
	add_object(triangle_ptr2);
	
	
	// brown triangle (transformed)
			
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->set_ka(0.25); 
	matte_ptr3->set_kd(0.75);
	matte_ptr3->set_cd(0.71, 0.40, 0.16);
	
	Instance* triangle_ptr3 = new Instance(new Triangle(Point3D(2, 0, 5), Point3D(2, 1, -5), Point3D(-1, 0, -4))); 
	triangle_ptr3->rotate_y(240);
	triangle_ptr3->set_material(matte_ptr3);
	add_object(triangle_ptr3);
}	
	
	
