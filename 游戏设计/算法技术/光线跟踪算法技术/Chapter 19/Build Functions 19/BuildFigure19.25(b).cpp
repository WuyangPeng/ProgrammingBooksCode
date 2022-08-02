// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 19.25(b).

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	background_color = white;
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 100); 
	pinhole_ptr->set_eye(0, 50, 100); 
	pinhole_ptr->set_lookat(0.0, 0.75, 0.0); 
	pinhole_ptr->set_view_distance(16000);           
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(10, 5, 20);		
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	
	
	ConeChecker* checker_ptr = new ConeChecker;
	checker_ptr->set_color1(0.85);
	checker_ptr->set_color2(0.85);
	checker_ptr->set_line_color(black);
	checker_ptr->set_vertical_line_width(0.075);
	checker_ptr->set_horizontal_line_width(0.075);
	checker_ptr->set_num_vertical_checkers(10);
	checker_ptr->set_num_horizontal_checkers(14);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.85); 
	sv_matte_ptr->set_cd(checker_ptr);	
	
	OpenCone* cone_ptr = new OpenCone;
	cone_ptr->set_material(sv_matte_ptr);
	add_object(cone_ptr);
	
}



