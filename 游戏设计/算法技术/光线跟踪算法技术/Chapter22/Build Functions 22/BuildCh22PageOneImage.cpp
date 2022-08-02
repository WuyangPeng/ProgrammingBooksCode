// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for the Chapter 22 page one image

void 												
World::build(void){
	int num_samples = 1;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0.0, 0.0, 0.9);
	pinhole_ptr->set_lookat(0, 0, -100);
	pinhole_ptr->set_view_distance(150); 
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	Directional* light_ptr = new Directional;   
	light_ptr->set_direction(0, 0, 1);				
	light_ptr->scale_radiance(3.0);   
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	int num_spheres = 1000;
	float volume = 0.1 / num_spheres;
	float radius = pow(0.75 * volume / 3.14159, 0.333333);
	
	set_rand_seed(15);
	
	Grid* grid_ptr = new Grid;  
	
	for (int j = 0; j < num_spheres; j++) {
		Matte* matte_ptr = new Matte;
		matte_ptr->set_ka(0.25);
		matte_ptr->set_kd(0.75);
		matte_ptr->set_cd(RGBColour(rand_float(), rand_float(), rand_float()));
		
		Sphere*	sphere_ptr = new Sphere; 
		sphere_ptr->set_radius(radius);
		sphere_ptr->set_center(	1.0 - 2.0 * rand_float(), 
								1.0 - 2.0 * rand_float(), 
								1.0 - 2.0 * rand_float());	
		sphere_ptr->set_material(matte_ptr);
		grid_ptr->add_object(sphere_ptr);
	}	

	grid_ptr->setup_cells();
	add_object(grid_ptr);
}


