// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.4
// Some shadows on the bunnies look black because ls = 0.5 in the ambient light
// and ka = 0.25 in the materials

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(350); 
	vp.set_samples(num_samples);	
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
		
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinHole_ptr = new Pinhole;
	pinHole_ptr->set_eye(7.7, 6, 15);
	pinHole_ptr->set_lookat(-1.0, -0.5, 0); 
	pinHole_ptr->set_view_distance(650);
	pinHole_ptr->compute_uvw();
	set_camera(pinHole_ptr);
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(30, 30, 25); 
	light_ptr1->set_location(30, 20, -10);  
	light_ptr1->scale_radiance(2.5);  
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(10, 20, 40);  
	light_ptr2->scale_radiance(1.5);  
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	// ground plane 
	
	Matte* matte_ptr1 = new Matte;		
	matte_ptr1->set_ka(0.35);
	matte_ptr1->set_kd(0.75);
	matte_ptr1->set_cd(white);  
	
	Plane* planePr1 = new Plane(Point3D(0, 0.24, 0), Normal(0, 1, 0));
	planePr1->set_material(matte_ptr1);
	add_object(planePr1);

				
	float 	x0 					= -5.0;					// minimum x center coordinate
	float 	z0 					= -5.0;					// minimum z center coordinate
	float 	x1 					= 5.0;					// minimum x center coordinate
	float 	z1 					= 5.0;					// minimum z center coordinate
	int 	num_x_bunnies		= 8;					// number of bunnies in the x direction
	int 	num_z_bunnies		= 8;  					// number of bunnies in the z direction
	float	x_spacing			= (x1 - x0) / (num_x_bunnies - 1); // center spacing in x direction
	float	z_spacing			= (z1 - z0) / (num_z_bunnies - 1); // center spacing in x direction
	
	
	const char* fileName = "Bunny16K.ply"; 
	
	Grid* bunny_ptr1 = new Grid(new Mesh);
	bunny_ptr1->read_smooth_triangles(fileName);
	bunny_ptr1->setup_cells();
	
	set_rand_seed(1000);
	Grid* grid_ptr = new Grid;
	
	for (int iz = 0; iz < num_z_bunnies; iz++)
		for (int ix = 0; ix < num_x_bunnies; ix++) {
			Phong* phong_ptr = new Phong;	
			phong_ptr->set_ka(0.25); 
			phong_ptr->set_kd(0.75);
			phong_ptr->set_cd(rand_float(), rand_float(), rand_float());
			phong_ptr->set_ks(0.125);  
			phong_ptr->set_exp(20.0);
			
			Instance* bunny_ptr2 = new Instance(bunny_ptr1);
			bunny_ptr2->set_material(phong_ptr);
			bunny_ptr2->scale(6.5);
			bunny_ptr2->translate(x0 + ix * x_spacing, 0, z0 + iz * z_spacing);
			bunny_ptr2->set_bounding_box(); // essential for placing each bunny in the grid
			grid_ptr->add_object(bunny_ptr2);
		}

	grid_ptr->setup_cells();
	add_object(grid_ptr);
}

