// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.15(c)

// This shows the true size of the diamond sphere, instead of its enlarged,
// refracted image as seen in Figures 28.15 (a) and (b).
// Note that eta_out and cf_out are different from their values in Figures 28.15 (a) and (b).

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(7);

	background_color = RGBColor(0.0, 0.3, 0.25);  // blue green
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0.5, 40.0, 0.5);
	pinhole_ptr->set_lookat(0.5, 0.0, 0.5);
	pinhole_ptr->set_view_distance(3000.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);

	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 1, 0);      // straight down
	light_ptr->scale_radiance(7.5);   
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	

	// nested spheres
	
	RGBColor glass_color(0.95, 0.95, 1);  	// faint blue
	RGBColor diamond_color(1, 1, 0.8);  	// lemon
	RGBColor water_color(1, 0.5, 1);  		// mauve
	
	Point3D center(0.5, 0, 0.5);  			// common centre
	
	
	// outer sphere - glass
	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_ks(0.1);   
	glass_ptr->set_exp(2000.0);
	glass_ptr->set_eta_in(1.5); 			// water
	glass_ptr->set_eta_out(1.0);			// air
	glass_ptr->set_cf_in(glass_color);
	glass_ptr->set_cf_out(white);
			
	Sphere* sphere_ptr1 = new Sphere(center, 3.5);
	sphere_ptr1->set_material(glass_ptr);
//	add_object(sphere_ptr1);
	
	
	// middle sphere - diamond
	
	Dielectric* diamond_ptr = new Dielectric;
	diamond_ptr->set_ks(0.1);    
	diamond_ptr->set_exp(2000.0);
	diamond_ptr->set_eta_in(2.42); 			// diamond
	diamond_ptr->set_eta_out(1.0);			// air
	diamond_ptr->set_cf_in(diamond_color);
	diamond_ptr->set_cf_out(white);
	
	Sphere* sphere_ptr2 = new Sphere(center, 2.0);
	sphere_ptr2->set_material(diamond_ptr);
	add_object(sphere_ptr2);
	
	
	// inner sphere - water
	
	Dielectric* water_ptr = new Dielectric;
	water_ptr->set_ks(0.1);  
	water_ptr->set_exp(2000.0);
	water_ptr->set_eta_in(1.33); 			// water
	water_ptr->set_eta_out(2.42); 			// diamond
	water_ptr->set_cf_in(water_color);
	water_ptr->set_cf_out(diamond_color);
	
	Sphere* sphere_ptr3 = new Sphere(center, 0.6);
	sphere_ptr3->set_material(water_ptr);
//	add_object(sphere_ptr3);
	
	
	// ground plane

	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(2.0);
	checker_ptr->set_color1(0.25); 
	checker_ptr->set_color2(white);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.35);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -6.5, 0), Normal(0, 1, 0));  
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);
}


