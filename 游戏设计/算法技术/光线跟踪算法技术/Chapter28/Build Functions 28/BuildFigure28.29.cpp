// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This renders the scene for Figure 28.29

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(6);

	background_color = RGBColor(0.0, 0.13, 0.1);

	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->set_color(0.45, 0.5, 0.45);
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);

	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 10);
	pinhole_ptr->set_lookat(0, 0, 0);    
	pinhole_ptr->set_view_distance(2800.0);		
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
		
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(10, 10, 10);   
	light_ptr1->scale_radiance(7.0);  
	light_ptr1->set_shadows(false);
	add_light(light_ptr1);
		
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(-1, 0, 0);   
	light_ptr2->scale_radiance(7.0);  
	light_ptr2->scale_radiance(13.0);  
	light_ptr2->set_shadows(false);
	add_light(light_ptr2);
	

	// transparent unit sphere at the origin
		
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_eta_in(2.42);		// glass
	dielectric_ptr->set_eta_out(1.0);		// air
	dielectric_ptr->set_cf_in(white);
	dielectric_ptr->set_cf_out(white); 
		
	Sphere* sphere_ptr1 = new Sphere;
	sphere_ptr1->set_material(dielectric_ptr);
	
	
	// red reflective sphere inside the transparent sphere
	// the red comes from the diffuse color
	
	// the Reflective parameters below are for the reflective sphere in a diamond sphere
			
	Reflective*	reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.1);	
	reflective_ptr->set_kd(1.0);  
	reflective_ptr->set_cd(red);
	reflective_ptr->set_ks(0.3);  
	reflective_ptr->set_exp(200.0);
	reflective_ptr->set_kr(0.75);
	reflective_ptr->set_kr(1.0);
	reflective_ptr->set_cr(white);
	
	double radius = 0.1;
	double distance = 0.8;   // from center of transparent sphere 
		
	Sphere* sphere_ptr2 = new Sphere(Point3D(0, 0, distance), radius);
	sphere_ptr2->set_material(reflective_ptr);
	
	// store the spheres in a compound object
	
	Compound* spheres_ptr = new Compound;
	spheres_ptr->add_object(sphere_ptr1);
	spheres_ptr->add_object(sphere_ptr2);
	
	// now store compound object in an instance so that we can rotate it
	
	Instance* rotated_spheres_ptr = new Instance(spheres_ptr);
	rotated_spheres_ptr->rotate_y(172.5);	// for Figure 28.29(a)
//	rotated_spheres_ptr->rotate_y(173.0);  	// for Figure 28.29(b)
//	rotated_spheres_ptr->rotate_y(178.0);  	// for Figure 28.29(c)
	add_object(rotated_spheres_ptr);
	
	
	// ground plane
	
	Checker3D* checker3D_ptr = new Checker3D;
	checker3D_ptr->set_size(50.0); 
	checker3D_ptr->set_color1(0.5); 
	checker3D_ptr->set_color2(1.0); 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.5);
	sv_matte_ptr->set_cd(checker3D_ptr);
		
	Plane* plane_ptr = new Plane(Point3D(0, -40.5, 0), Normal(0, 1, 0));  
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);
}


