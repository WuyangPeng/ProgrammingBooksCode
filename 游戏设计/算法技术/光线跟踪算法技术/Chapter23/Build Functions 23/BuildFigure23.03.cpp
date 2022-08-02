// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 23.3.

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);

	background_color = RGBColour(0.9);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 12, 18); 
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->set_view_distance(4000); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
			

	Directional* light_ptr = new Directional;
	light_ptr->set_direction(20, 25, 5);
	light_ptr->scale_radiance(3.0);   
	light_ptr->set_shadows(false);
	add_light(light_ptr);	
	
	
	Phong* phong_ptr = new Phong;
	phong_ptr->set_ka(0.25);
	phong_ptr->set_kd(0.75);
	phong_ptr->set_cd(0.5);
	phong_ptr->set_cd(0.2, 0.5, 0.4);
	phong_ptr->set_ks(0.2);
	phong_ptr->set_exp(20.0);
	
	// 360 must be divisible by num_horizontal_steps
	// 180 must be divisible by num_vertical_steps
	
	int num_horizontal_steps = 3;    	// for Figure 23.3(a)
	int num_vertical_steps = 2;
	
//	int num_horizontal_steps = 4;		// for Figure 23.3(b)
//	int num_vertical_steps = 2;
	
//	int num_horizontal_steps = 10;		// for Figure 23.3(c)
//	int num_vertical_steps = 5;
	
//	int num_horizontal_steps = 100;		// for Figure 23.3(d)
//	int num_vertical_steps = 50;
		
	Grid* grid_ptr = new Grid;
	grid_ptr->tessellate_smooth_sphere(num_horizontal_steps, num_vertical_steps); 
	grid_ptr->set_material(phong_ptr);
	grid_ptr->setup_cells();
	add_object(grid_ptr);	
}


