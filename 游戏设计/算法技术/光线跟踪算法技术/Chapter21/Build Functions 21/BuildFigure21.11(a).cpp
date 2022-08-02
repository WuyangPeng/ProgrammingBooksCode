// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.11(a)
// The marble texture is discussed in Chapter 31 

void 												
World::build(void) {
	int num_samples = 1;

	vp.set_hres(600);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(50, 50, 30);			
	pinhole_ptr->set_lookat(0);
	pinhole_ptr->set_view_distance(5000);  
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(20, 30, 30);
	light_ptr2->scale_radiance(2.0);   
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
		
	// rosette parameters
	
	int		num_rings = 3;		// maximum of 6
	float	hole_radius = 0.75;
	float	ring_width = 1.0;
	float	rb = 0.1;			// bevel radius
	float	y0 = -0.25;			// minimum y value
	float 	y1 = 0.25;			// minimum y value
	
		
	Rosette* rosette_ptr = new Rosette(num_rings, hole_radius, ring_width, rb, y0, y1);
	
	// put a different random marble texture on each wedge
	
	// blue marble ramp image
	
	Image* image_ptr1 = new Image;						
	image_ptr1->read_ppm_file("BlueMarbleRamp.ppm");
	
	// marble texture parameters
	
	int num_octaves = 4;
	float lacunarity = 2.0;
	float gain = 0.5;
	float perturbation = 3.0;
	
	int num_objects = rosette_ptr->get_num_objects();
	
	for (int j = 0; j < num_objects; j++) {
		
		RampFBmTexture* blue_marble_ptr = new RampFBmTexture(image_ptr1);   // blue marble
		blue_marble_ptr->set_num_octaves(num_octaves);
		blue_marble_ptr->set_lacunarity(lacunarity);
		blue_marble_ptr->set_gain(gain);
		blue_marble_ptr->set_perturbation(perturbation);
		
		// transformed marble texture

		TInstance* wedge_marble_ptr = new TInstance(blue_marble_ptr);
		set_rand_seed(j * 10);
		wedge_marble_ptr->scale(0.25);
		wedge_marble_ptr->rotate_x(20.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->rotate_y(30.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->rotate_z(45.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->translate(10.0 * (2.0 * rand_float() - 1.0), 20.0 * (2.0 * rand_float() - 1.0), 30.0 * (2.0 * rand_float() - 1.0));
		
		// marble material

		SV_Matte* sv_matte_ptr = new SV_Matte;		
		sv_matte_ptr->set_ka(0.35);
		sv_matte_ptr->set_kd(0.75);
		sv_matte_ptr->set_cd(wedge_marble_ptr);
		
		rosette_ptr->store_material(sv_matte_ptr, j);	// store material in the specified wedge
	}
	
	rosette_ptr->setup_cells();
	add_object(rosette_ptr);
}

