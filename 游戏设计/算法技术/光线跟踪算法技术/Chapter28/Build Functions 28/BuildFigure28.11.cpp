// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.11 and the extra images in the Chapter 28 download

void 												
World::build(void) {
	int num_samples = 25;  
	
	vp.set_hres(600);	 		
	vp.set_vres(600);
	vp.set_max_depth(6);  
	vp.set_samples(num_samples);
	
	background_color = white;
	
	tracer_ptr = new Whitted(this);
	
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 2, 20);  
	pinhole_ptr->set_lookat(0.25, 4, 0);
	pinhole_ptr->set_view_distance(1275.0); 	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
		
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(2, 3, 0.5);
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// lens
	
	RGBColor glass_color(0.65, 0.45, 0);   // orange 	for Figure 28.11(a)
//	RGBColor glass_color(0.0, 0.5, 0.5);   // cyan		for Figure 28.11(b)
	
	// extra imgages
	
//	RGBColor glass_color(0.5, 0.0, 0.5);   // majenta
//	RGBColor glass_color(0, 0.65, 0.35);   // blue-green
//	RGBColor glass_color(0.0, 0.35, 0.65); // blue

	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_eta_in(1.5);				// glass
	glass_ptr->set_eta_out(1.0);			// air
	glass_ptr->set_cf_in(glass_color);
	glass_ptr->set_cf_out(1, 1, 1); 
	

	double radius 		= 4.0;
	double thickness 	= 2.0;
//	double min_distance = 0.35;  			// for cyan
	double min_distance = 0.1;   			// for all other colours
	

	Instance* concave_lens_ptr = new Instance(new ConcaveLens(radius, thickness, min_distance));
	concave_lens_ptr->set_material(glass_ptr);
	concave_lens_ptr->rotate_x(90);
	concave_lens_ptr->translate(0.0, radius, 0.0);
	add_object(concave_lens_ptr);
	
	
	// plane with checker
	
	PlaneChecker* plane_checker_ptr = new PlaneChecker;
	plane_checker_ptr->set_size(3);		
	plane_checker_ptr->set_outline_width(0.4);
	plane_checker_ptr->set_color1(white);
	plane_checker_ptr->set_color2(white);  
	plane_checker_ptr->set_outline_color(0.25); 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.65);
	sv_matte_ptr->set_cd(plane_checker_ptr);

	Plane* plane_ptr = new Plane(Point3D(0, 0, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr);
	plane_ptr->set_shadows(false);
	add_object(plane_ptr);	
}

