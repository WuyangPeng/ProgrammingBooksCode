// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.11(b)

// The archway and wall are constructed in the (x, z) plane, and then rotated and translated into position.
// The archway is a class called Archway, but the wall is a plain Grid.
// The blocks are only added to the wall if they are not inside the archway.
// The code here is just to get you started, with the archway testing hardwired in.
// A systematic approach would be to implement a Wall class that has a list of doors and windows that it
// can check the blocks against, using a common user interface.
// The doors and windows should be able to be transformed with the wall.
// The beveled wedges can also be used to build circular towers, again with doors and windows

void 												
World::build(void) {
	int num_samples = 1;

	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	background_color = RGBColour(0.4, 0.4, 0.8);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(20, 12.5, 30);		
	pinhole_ptr->set_lookat(1, 11.6, 0.0);
	pinhole_ptr->set_view_distance(440); 	
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(-20, 30, 30);
	light_ptr2->scale_radiance(3);  
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
		
	// archway parameters
	
	float 	width			= 20.0;		
	float 	height			= 25.0;		
	float 	depth			= 3.0;	
	float 	column_width  	= 4.0;
	int 	num_blocks		= 6;
	int 	num_wedges		= 10;
	float 	bevel_radius	= 0.5;
				
	Archway* archway_ptr = new Archway(width, height, depth, column_width, num_blocks, num_wedges, bevel_radius);
	
	// put a different random sandstone texture on each archway component
	
	// sandstone parameters
	
	int num_octaves = 4;
	float lacunarity = 2.0;
	float gain = 0.5;
	float perturbation = 0.1; 
	
	// sandstone ramp image
	
	Image* image_ptr1 = new Image;						
	image_ptr1->read_ppm_file("Sandstone1.ppm");
	
	int num_objects = archway_ptr->get_num_objects();
	
	for (int j = 0; j < num_objects; j++) {
		
		RampFBmTexture* marble_ptr = new RampFBmTexture(image_ptr1); 
		marble_ptr->set_num_octaves(num_octaves);
		marble_ptr->set_lacunarity(lacunarity);
		marble_ptr->set_gain(gain);
		marble_ptr->set_perturbation(perturbation);
		
		// transformed marble texture

		TInstance* wedge_marble_ptr = new TInstance(marble_ptr);
		set_rand_seed(j * 10);
		wedge_marble_ptr->scale(0.5); 
		wedge_marble_ptr->rotate_x(20.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->rotate_y(30.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->rotate_z(45.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->translate(10.0 * (	2.0 * rand_float() - 1.0), 
												20.0 * (2.0 * rand_float() - 1.0), 
												30.0 * (2.0 * rand_float() - 1.0));
		
		// marble material

		SV_Matte* sv_matte_ptr = new SV_Matte;		
		sv_matte_ptr->set_ka(0.35);
		sv_matte_ptr->set_kd(0.85);
		sv_matte_ptr->set_cd(wedge_marble_ptr);
		
		archway_ptr->store_material(sv_matte_ptr, j);	
	}
	
	archway_ptr->setup_cells();
	
	Instance* door_ptr = new Instance(archway_ptr);
	door_ptr->rotate_z(90);
	door_ptr->rotate_y(90);
	door_ptr->translate(0.0, height - width / 2.0, 0.0);
	add_object(door_ptr);
	
	
	
	// build a wall of blocks that has the archway going through it 
	
	// wall parameters
	
	float wall_height 		= 40;   // x direction
	float wall_length 		= 100; 	// z direction
	float wall_thickness 	= 3;	// y direction
	int num_blocks_per_row 	= 40;
	int num_rows			= 20;
	float offset			= wall_thickness / 4.0; // wall is offset back from the front of the archway
	
	float block_length = wall_length / num_blocks_per_row;   // z dimension of blocks
	float block_height = wall_height / num_rows;			// x dimension of blocks
	float block_offset	= block_length / 2.0; 
	
	Grid* wall_ptr = new Grid;
	
	for (int k = 0; k < num_rows / 2; k ++) {
		for (int j = 0; j < num_blocks_per_row; j++) {   // first row
		
			Point3D p0(	-(height - width / 2.0) + 2 * k * block_height, 
						-offset, 
						- wall_length / 2.0 + j * block_length);
			Point3D p1(	-(height - width / 2.0) + (2 * k + 1) * block_height, 
						-offset + wall_thickness, 
						- wall_length / 2.0 + (j + 1) * block_length);
			BeveledBox* block_ptr = new BeveledBox(p0, p1, bevel_radius);
			
			// only add the block to the wall if it isn't inside the archway
			
			BBox bbox = block_ptr->get_bounding_box();
			
			bool in_rectangle = 	bbox.z0 < (width / 2.0 - column_width + bevel_radius)
								&& 	bbox.z1 > (-width / 2.0 + column_width - bevel_radius)
								&&	bbox.x0 < 0.0;	
								
			float r_squared = (width / 2.0 - column_width + bevel_radius) * (width / 2.0 - column_width + bevel_radius);
			float d0 = bbox.x0 * bbox.x0 + bbox.z0 * bbox.z0;	// lower left
			float d1 = bbox.x0 * bbox.x0 + bbox.z1 * bbox.z1;	// lower right
			float d2 = bbox.x1 * bbox.x1 + bbox.z1 * bbox.z1;	// upper right	
			float d3 = bbox.x1 * bbox.x1 + bbox.z0 * bbox.z0;	// upper left	
			
			bool in_circle = d0 < r_squared || d1 < r_squared || d2 < r_squared || d3 < r_squared && bbox.x0 > block_height;						
										
			if (!in_rectangle && !in_circle)																					
				wall_ptr->add_object(block_ptr);		
		}
		
		for (int j = 0; j < num_blocks_per_row; j++) {   // second row - offset in the z direction by half a block length

			Point3D p0(	-(height - width / 2.0) + (2 * k + 1) * block_height, 
						-offset, 
						- wall_length / 2.0 + j * block_length + block_offset);
			Point3D p1(	-(height - width / 2.0) + (2 * k + 2) * block_height, 
						-offset + wall_thickness, 
						-wall_length / 2.0 + (j + 1) * block_length + block_offset);
			BeveledBox* block_ptr = new BeveledBox(p0, p1, bevel_radius);
			
			// only add the block to the wall if it isn't inside the archway
			
			BBox bbox = block_ptr->get_bounding_box();
			
			bool in_rectangle = 	bbox.z0 < (width / 2.0 - column_width + bevel_radius)
								&& 	bbox.z1 > (-width / 2.0 + column_width - bevel_radius)
								&&	bbox.x0 < 0.0;									
										
			float r_squared = (width / 2.0 - column_width + bevel_radius) * (width / 2.0 - column_width + bevel_radius);
			float d0 = bbox.x0 * bbox.x0 + bbox.z0 * bbox.z0;	// lower left
			float d1 = bbox.x0 * bbox.x0 + bbox.z1 * bbox.z1;	// lower right
			float d2 = bbox.x1 * bbox.x1 + bbox.z1 * bbox.z1;	// upper right	
			float d3 = bbox.x1 * bbox.x1 + bbox.z0 * bbox.z0;	// upper left	
			
			bool in_circle = d0 < r_squared || d1 < r_squared || d2 < r_squared || d3 < r_squared && bbox.x0 > block_height;							
										
			if (!in_rectangle && !in_circle)																					
				wall_ptr->add_object(block_ptr);				
		}		
	}
	
	
	// use a different random marble texture on each block
	// the marble paramters are the same as the sandstone's, except for the perturbation:
	
	perturbation = 3.0; 
	
	// gray marble ramp image
	
	Image* image_ptr2 = new Image;						
	image_ptr2->read_ppm_file("GrayMarbleRamp2.ppm");
	
	num_objects = wall_ptr->get_num_objects();
	
	for (int j = 0; j < num_objects; j++) {
		
		RampFBmTexture* marble_ptr = new RampFBmTexture(image_ptr2);  
		marble_ptr->set_num_octaves(num_octaves);
		marble_ptr->set_lacunarity(lacunarity);
		marble_ptr->set_gain(gain);
		marble_ptr->set_perturbation(perturbation);
		
		// transformed marble texture

		TInstance* wedge_marble_ptr = new TInstance(marble_ptr);
		set_rand_seed(j * 10);
		wedge_marble_ptr->scale(0.25);
		wedge_marble_ptr->rotate_x(20.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->rotate_y(30.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->rotate_z(45.0 * (2.0 * rand_float() - 1.0));
		wedge_marble_ptr->translate(10.0 * (2.0 * rand_float() - 1.0), 
									20.0 * (2.0 * rand_float() - 1.0), 
									30.0 * (2.0 * rand_float() - 1.0));
		
		// marble material

		SV_Matte* sv_matte_ptr = new SV_Matte;		
		sv_matte_ptr->set_ka(0.25);
		sv_matte_ptr->set_kd(0.5);
		sv_matte_ptr->set_cd(wedge_marble_ptr);
		
		wall_ptr->store_material(sv_matte_ptr, j);	
	}
	
	wall_ptr->setup_cells();
	
	Instance* vertical_wall_ptr = new Instance(wall_ptr);
	vertical_wall_ptr->rotate_z(90);
	vertical_wall_ptr->rotate_y(90);
	vertical_wall_ptr->translate(0.0, height - width / 2.0, 0.0);
	add_object(vertical_wall_ptr);
	
	
	// ground plane
	
	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.25);
	matte_ptr->set_kd(0.5);
	matte_ptr->set_cd(0.35, 0.75, 0.35);
	
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);
}

