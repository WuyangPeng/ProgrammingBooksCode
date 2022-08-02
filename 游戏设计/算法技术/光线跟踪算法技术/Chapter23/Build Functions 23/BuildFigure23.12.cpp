// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 23.12

//  The grid parameters are slightly different from those in Listing 23.10:
// 	The number of levels is a more sane 6 instead of 8;
// 	The spacings between the bunnies and instance grids are different;
// 	The bunnies have random colors, but each level-0 10 x 10 array has the same random colors. See Extra_Image.jpg.

// The images rendered with this build function are in the Chapter 23 download.

// A level 8 structure needs about 250 MB of storage compared with about 15 MB for level 6. 
// On my 450 MZ Mac, the render times vary from about 8 seconds for the whole grid to about 
// 35 seconds for the closest zoom.
// Render times for whole grid do not vary much with the number of levels.

// This build function is unusual in that the camera is defined last. We need to define it
// last to keep the whole grid in view for all values of num_levels. The code above the
// camera computes the overall grid size.

// When zooming, you have to be careful not to zoom into one of the gaps between the instance grids.


void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(500);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	background_color = black;
	tracer_ptr = new RayCast(this);
	
	// the camera is defined at the bottom
		
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(20, 40, 20);
	light_ptr1->scale_radiance(3.0); 
	add_light(light_ptr1);
	
	
	Phong* phong_ptr = new Phong;
	phong_ptr->set_ka(0.2);
	phong_ptr->set_kd(0.5);
	phong_ptr->set_cd(1.0);
	phong_ptr->set_ks(0.4);
	phong_ptr->set_exp(20);
	
//	const char* fileName = "Bunny4K.ply";			// low res Stanford bunny
	const char* fileName = "Bunny16K.ply";			// medium res Stanford bunny
//	const char* fileName = "Bunny69K.ply";			// high res Stanford bunny

	Grid* bunny_ptr = new Grid(new Mesh);
	bunny_ptr->read_flat_triangles(fileName);		// read PLY file
//	bunny_ptr->read_smooth_triangles(fileName);		// read PLY file
//	bunny_ptr->set_material(phong_ptr);				// only use this if you want white bunnies
	bunny_ptr->setup_cells();
		
	int 	num_levels 			= 6;		// number of levels
	int 	instances_grid_res 	= 10; 		// each level consists of instances_grid_res x instances_grid_res instances
	double 	delta 				= 0.1; 		// gap between instances
	double 	gap 				= 0.08; 	// gap between bunnies in the level 0 grid
	double 	size 				= 0.1;    	// bunny size
	double 	mcx 				= 0.5; 		// camera coordinates as multiple mcx of grid size - allows us to keep the whole grid in view
	
	set_rand_seed(1000);
	
	Grid* current_grid_ptr = bunny_ptr;							// just the bunny
	
	for (int level = 0; level < num_levels; level++) {	
		Grid* instance_grid_ptr = new Grid;						// temporary grid
		
		for (int i = 0; i < instances_grid_res; i++) {   		// xw direction
			for (int k = 0; k < instances_grid_res; k++) {   	// zw direction
			
				Phong* phong_ptr = new Phong;
				phong_ptr->set_ka(0.2);
				phong_ptr->set_kd(0.5);
				phong_ptr->set_cd(rand_float(), rand_float(), rand_float());
				phong_ptr->set_ks(0.4);
				phong_ptr->set_exp(20);
			
				Instance* instance_ptr = new Instance;
				instance_ptr->set_object(current_grid_ptr); 	// add whole grid up to this level
				instance_ptr->set_material(phong_ptr);
				instance_ptr->translate(i * (size + gap), 0.0, k * (size + gap)); 
				instance_ptr->compute_bounding_box();
				instance_grid_ptr->add_object(instance_ptr);
			}
		}
		
		size = instances_grid_res * size + (instances_grid_res - 1) * gap;  
		gap = delta * size;
		instance_grid_ptr->setup_cells();
		current_grid_ptr = instance_grid_ptr;					// now the whole grid up to this level	
	}
	
	add_object(current_grid_ptr); 								// the whole n-level grid
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(7 * mcx * size, 4 * mcx * size, 5 * mcx * size); 
	pinhole_ptr->set_lookat(mcx * size, 0.0, mcx * size);     				// use this for the whole grid 
//	pinhole_ptr->set_lookat(mcx * size, 0.4 * mcx * size, mcx * size);   	// use this for the zooms
	pinhole_ptr->set_view_distance(1400);   		// Figure 23.12(a) the whole grid
//	pinhole_ptr->set_view_distance(140000);  		// Figure 23.12(b)
//	pinhole_ptr->set_view_distance(14000000);  		// Figure 23.12(c)
//	pinhole_ptr->set_view_distance(300000000);   	// Figure 23.12(d)
//	pinhole_ptr->set_view_distance(100000000);   	// extra image
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr); 
}
