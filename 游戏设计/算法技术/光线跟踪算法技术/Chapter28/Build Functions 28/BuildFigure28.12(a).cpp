// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.12 (a) & (b)

// In the 10K bunny PLY file the triangle vertices are ordered counter-clockwise when viewed
// from the outside. If you want to render this model, you must reverse the normals.
// This is an option on the Grid class.

// As the bunny is quite small, I've scaled it uniformly by a factor of 20 to make it easier
// to design the filter color.

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);	
	vp.set_max_depth(2);			
	
	background_color = white;
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 100);  
	pinhole_ptr->set_lookat(-0.4, 0.6, 0);    
	pinhole_ptr->set_view_distance(15000.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	// transparent bunny
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_ka(0.0);
	dielectric_ptr->set_kd(0.0); 
	dielectric_ptr->set_ks(0.2);     
	dielectric_ptr->set_exp(2000.0);
	dielectric_ptr->set_eta_in(1.5);   
	dielectric_ptr->set_eta_out(1.0);
	dielectric_ptr->set_cf_in(0.65, 0.45, 0);   // orange
	dielectric_ptr->set_cf_out(white);
		
//	const char* file_name = "Bunny4K.ply"; 		// 4000 triangles
//	const char* file_name = "Bunny10K.ply"; 	// 10000 triangles
//	const char* file_name = "Bunny16K.ply"; 	// 16000 triangles
	const char* file_name = "Bunny69K.ply"; 	// 69000 triangles


	Grid* bunny_ptr = new Grid(new Mesh);
//	bunny_ptr->reverse_mesh_normals();				// you must use this for the 10K model
//	bunny_ptr->read_flat_triangles(file_name);		
	bunny_ptr->read_smooth_triangles(file_name);
	bunny_ptr->set_material(dielectric_ptr); 	
	bunny_ptr->setup_cells();

	Instance* big_bunny_ptr = new Instance(bunny_ptr);
	big_bunny_ptr->scale(20.0);
	big_bunny_ptr->translate(0, -1.5, 0.0);
	add_object(big_bunny_ptr);
}


