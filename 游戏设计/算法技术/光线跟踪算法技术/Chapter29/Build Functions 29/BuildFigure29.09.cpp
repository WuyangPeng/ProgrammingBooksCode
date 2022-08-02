// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the sphere for Figure 29.9

void 												
World::build(void) {
	int num_samples = 25;
	
	vp.set_hres(700);      
	vp.set_vres(700);    
	vp.set_samples(num_samples);
		
	background_color = black;
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* camera_ptr = new Pinhole;
//	camera_ptr->set_eye(40, 20, 40); 			// for Figure29.9(a)
	camera_ptr->set_eye(0, 65, 0); 				// for Figure29.9(b)			
	camera_ptr->set_lookat(0.0); 
	camera_ptr->set_view_distance(17000.0);
	camera_ptr->compute_uvw();     
	set_camera(camera_ptr); 
	
	
	// image:					

	Image* image_ptr = new Image;				
	image_ptr->read_ppm_file("SphereGrid.ppm");
	
	
	// mapping:
	
	SphericalMap* map_ptr = new SphericalMap; 
	
	
	// image based texture:  
	
	ImageTexture* texture_ptr = new ImageTexture; 
	texture_ptr->set_image(image_ptr); 
	texture_ptr->set_mapping(map_ptr);
	
	
	// textured material:

	SV_Emissive* sv_emissive_ptr = new SV_Emissive;	
	sv_emissive_ptr->scale_radiance(1.0);	
	sv_emissive_ptr->set_ce(texture_ptr);
	
	
	// generic sphere:
	
	Sphere*	sphere_ptr = new Sphere; 
	sphere_ptr->set_material(sv_emissive_ptr);
	add_object(sphere_ptr);
}


