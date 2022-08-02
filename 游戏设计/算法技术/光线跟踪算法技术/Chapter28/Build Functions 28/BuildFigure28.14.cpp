// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.14

void 												
World::build(void) {
	int num_samples = 16;

	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);	
	vp.set_max_depth(9);		
	
	background_color = white;
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 100);  
	pinhole_ptr->set_lookat(0, -1.5, 0);    
	pinhole_ptr->set_view_distance(15000.0);	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
		
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 0, 1); 
	light_ptr->scale_radiance(5.0);
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	
	
	// transparent horse
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ka(0.0);
	dielectric_ptr->set_kd(0.0); 
	dielectric_ptr->set_ks(0.2);    
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.5);   
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(0.35, 0.65, 0.45);   // green
	dielectric_ptr->set_cf_out(white);
	
	const char* file_name = "Horse97K.ply"; 	

	Grid* horse_ptr = new Grid(new Mesh);
//	horse_ptr->read_flat_triangles(file_name);	
	horse_ptr->read_smooth_triangles(file_name);	
	horse_ptr->set_material(dielectric_ptr); 	
	horse_ptr->setup_cells();

	Instance* big_horse_ptr = new Instance(horse_ptr);
	big_horse_ptr->scale(5.0);
	big_horse_ptr->translate(0, -1.5, 0.0);
	add_object(big_horse_ptr);
	
	
	// vertical checker plane
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.0);		
	checker_ptr->set_color1(white);
	checker_ptr->set_color2(0.75);  
	
	PlaneChecker* plane_checker_ptr = new PlaneChecker;
	plane_checker_ptr->set_size(1.5);		
	plane_checker_ptr->set_outline_width(0.2);
	plane_checker_ptr->set_color1(white);
	plane_checker_ptr->set_color2(white);  
	plane_checker_ptr->set_outline_color(black); 
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.65);
	sv_matte_ptr->set_cd(plane_checker_ptr);

	Instance* plane_ptr = new Instance(new Plane(Point3D(0), Normal(0, 1, 0)));
	plane_ptr->set_material(sv_matte_ptr);
	plane_ptr->rotate_x(90);
	plane_ptr->translate(0, 0, -4);
	plane_ptr->set_shadows(false);
	add_object(plane_ptr);	
}


