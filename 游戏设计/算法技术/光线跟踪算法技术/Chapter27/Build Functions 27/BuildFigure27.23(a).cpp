// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 27.23(a)
// This uses the Dielectric material from Chapter 28

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_max_depth(3);      
	vp.set_samples(num_samples);
	
	background_color = RGBColor(0.75);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	tracer_ptr = new Whitted(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 20);
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(4500); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
		
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(0, 50, 0);
	light_ptr1->scale_radiance(4.5);
	light_ptr1->set_shadows(false);
	add_light(light_ptr1);
	
	
	// transparent sphere
	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_ks(0.15);
	glass_ptr->set_exp(100.0);
	glass_ptr->set_eta_in(1.5);
	glass_ptr->set_eta_out(1.0);
	glass_ptr->set_cf_in(0.47, 0.86, 0.74);
	glass_ptr->set_cf_out(white);
			
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_material(glass_ptr);
	add_object(sphere_ptr);                
	
	
	// plane with checker
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(4.0);		
	checker_ptr->set_color1(white);  	
	checker_ptr->set_color2(black);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.65);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -5, 0), Normal(0, 1, 0));  
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);	
}

