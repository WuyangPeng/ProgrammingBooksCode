// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 17.6

void 												
World::build(void) {
//	int num_samples = 1;   	// for Figure 17.7(a)
	int num_samples = 16;  	// for Figure 17.7(b)
//	int num_samples = 64;  	// for Figure 17.7(c)
//	int num_samples = 256;	// for Figure 17.7(d)
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);  
	
	tracer_ptr = new RayCast(this);
		
	MultiJittered* sampler_ptr = new MultiJittered(num_samples); 
	
	AmbientOccluder* occluder_ptr = new AmbientOccluder;
	occluder_ptr->scale_radiance(1.0);
	occluder_ptr->set_min_amount(0.0);
	occluder_ptr->set_sampler(sampler_ptr);
	set_ambient_light(occluder_ptr);		
	
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(25, 20, 45);
	pinhole_ptr->set_lookat(0, 1, 0); 
	pinhole_ptr->set_view_distance(5000);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	// sphere
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_ka(0.75);		
	matte_ptr1->set_kd(0);
	matte_ptr1->set_cd(1, 1, 0);   // yellow
		
	Sphere* sphere_ptr = new Sphere (Point3D(0, 1, 0), 1);  
	sphere_ptr->set_material(matte_ptr1);
	add_object(sphere_ptr);	
	
	// ground plane
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.75);		
	matte_ptr2->set_kd(0);
	matte_ptr2->set_cd(1);        // white
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);	
}


