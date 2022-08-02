// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 30.11(d)

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	background_color = RGBColor(0.5);	
	
	Pinhole* pinhole_ptr = new Pinhole;		
	pinhole_ptr->set_eye(0, 0, 100);
	pinhole_ptr->set_lookat(0.0);	
	pinhole_ptr->set_view_distance(7500.0);  
	pinhole_ptr->compute_uvw();  
	set_camera(pinhole_ptr);	
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 0, 1); 
	light_ptr->scale_radiance(3.0);
	add_light(light_ptr);
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(0.3);
	checker_ptr->set_color1(white);
	checker_ptr->set_color2(black);
		
	TInstance* scaled_checker_ptr = new TInstance(checker_ptr);
	scaled_checker_ptr->scale(2, 1, 1);
	 
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.8);  
	sv_matte_ptr->set_kd(0.4);
	sv_matte_ptr->set_cd(scaled_checker_ptr);
	
	Box* box_ptr = new Box(Point3D(-1.0), Point3D(1.0));
	box_ptr->set_material(sv_matte_ptr);

	Instance* transformed_box_ptr = new Instance(box_ptr);
	transformed_box_ptr->scale(2, 1, 1);
	transformed_box_ptr->rotate_z(45);
	add_object(transformed_box_ptr);
}


