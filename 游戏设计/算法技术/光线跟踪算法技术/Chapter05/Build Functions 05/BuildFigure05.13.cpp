// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 5.13
// Figure 5.13(a) is rendered using the function Sampler::sample_unit_square() in Listing 5.8
// This causes the streaks on the lower part of the reflective sphere
// Figure 5.13(b) is rendered using the function Sampler::sample_unit_square() in Listing 5.13
// which removes the streaks

void 												
World::build(void) {
	int num_samples = 16;
	Sampler* sampler_ptr = new MultiJittered(num_samples);

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_max_depth(1);
	vp.set_sampler(sampler_ptr);	

	background_color = black;

	tracer_ptr = new AreaLighting(this);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(30, 13, 20);
	pinhole_ptr->set_lookat(0, -2, 0); 
	pinhole_ptr->set_view_distance(12000); 
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 

	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->scale_radiance(3.0);
	emissive_ptr->set_ce(white);
	
	Rectangle* rectangle_ptr = new Rectangle(Point3D(-1, -0.5, -1), Vector3D(2, 0, 0), Vector3D(0, 0, 2), Normal(0, -1, 0));
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(sampler_ptr);
	add_object(rectangle_ptr);
	
	AreaLight* rectangularLight_ptr = new AreaLight;
	rectangularLight_ptr->set_object(rectangle_ptr);
	rectangularLight_ptr->set_shadows(true);
	add_light(rectangularLight_ptr);
	
	
	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.2); 
	reflective_ptr1->set_kd(0.1); 
	reflective_ptr1->set_cd(0, 1, 0.2);  // green
	reflective_ptr1->set_ks(0.0);     
	reflective_ptr1->set_exp(1);
	reflective_ptr1->set_kr(0.85); 
	reflective_ptr1->set_cr(0.75, 0.75, 1);  // blue 

	Sphere* sphere_ptr1 = new Sphere(Point3D(0, -2, 0), 0.5); 	
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);

		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1);		
	checker_ptr->set_color1(1.0);  
	checker_ptr->set_color2(0.9);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.75);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -2.75, 0), Normal(0, 1, 0));  
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);	
}




