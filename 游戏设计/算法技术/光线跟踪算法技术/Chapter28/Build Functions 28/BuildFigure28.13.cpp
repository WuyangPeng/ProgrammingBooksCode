// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This renders the scene for Figure 28.13

void 												
World::build(void) {
	int num_samples = 16;

	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(1);	
	vp.set_max_depth(9);		
	
	background_color = white;
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
	
	tracer_ptr = new Whitted(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 100);  
	pinhole_ptr->set_lookat(-0.15, -0.45, 0);    
	pinhole_ptr->set_view_distance(30000.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	// directional light 
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 0, 1); 
	light_ptr->scale_radiance(5.0);
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	
	
	// transparent bunny
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ka(0.0);
	dielectric_ptr->set_kd(0.0); 
	dielectric_ptr->set_ks(0.2);    
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.5);   
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(0.35, 0.65, 0.45);   // green
	dielectric_ptr->set_cf_out(white);
		
	const char* file_name = "Bunny4K.ply"; 				// for Figure 28.13(a)
//	const char* file_name = "Bunny16K.ply"; 			// for Figure 28.13(b)
//	const char* file_name = "Bunny69K.ply"; 			// for Figure 28.13(c)


	Grid* bunny_ptr = new Grid(new Mesh);
//	bunny_ptr->read_flat_triangles(file_name);			// for Figure 28.13(b)
	bunny_ptr->read_smooth_triangles(file_name);		// for Figures 28.13 (a) & (c)	
	bunny_ptr->set_material(dielectric_ptr); 	
	bunny_ptr->setup_cells();

	Instance* big_bunny_ptr = new Instance(bunny_ptr);
	big_bunny_ptr->scale(10.0);
	big_bunny_ptr->translate(0, -1.5, 0.0);
	add_object(big_bunny_ptr);
	
	
	// vertical checker plane
	
	PlaneChecker* plane_checker_ptr = new PlaneChecker;
	plane_checker_ptr->set_size(0.75);		
	plane_checker_ptr->set_outline_width(0.1);
	plane_checker_ptr->set_color1(white);
	plane_checker_ptr->set_color2(white);  
	plane_checker_ptr->set_outline_color(black); 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.65);
	sv_matte_ptr->set_cd(plane_checker_ptr);
	
	// my PlaneChecker texture is only defined for planes parallel to the (x, z) plane
	// necessitating the use of an instance for a vertical plane

	Instance* plane_ptr = new Instance(new Plane(Point3D(0), Normal(0, 1, 0)));
	plane_ptr->set_material(sv_matte_ptr);
	plane_ptr->rotate_x(90);
	plane_ptr->translate(0, 0, -2);
	plane_ptr->set_shadows(false);
	add_object(plane_ptr);	
		
}


