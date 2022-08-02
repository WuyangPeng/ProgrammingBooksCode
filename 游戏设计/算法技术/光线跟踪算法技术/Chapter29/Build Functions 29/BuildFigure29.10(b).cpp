// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.10(b)

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_samples(num_samples);
	
	background_color = black;
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(0, -65, 0); 
	camera_ptr->set_lookat(0.0); 
	camera_ptr->set_view_distance(12000.0); 
	camera_ptr->compute_uvw();     
	set_camera(camera_ptr); 
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, -1, 0);
	light_ptr->scale_radiance(1.5);  
	add_light(light_ptr);
	
	
	// image:					

	Image* image_ptr = new Image;				
	image_ptr->read_ppm_file("Sarah.ppm");
	
	
	// mapping:
	
	SphericalMap* map_ptr = new SphericalMap; 
	
	
	// image based texture:  
	
	ImageTexture* texture_ptr = new ImageTexture; 
	texture_ptr->set_image(image_ptr); 
	texture_ptr->set_mapping(map_ptr);
	
	
	// textured material:

	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.45);
	sv_matte_ptr->set_kd(0.65);
	sv_matte_ptr->set_cd(texture_ptr);
	
	
	// generic sphere:
	
	Sphere*	sphere_ptr = new Sphere; 
	sphere_ptr->set_material(sv_matte_ptr);
	
	
	// rotated sphere
	
	Instance* sarah_ptr = new Instance(sphere_ptr);
	sarah_ptr->rotate_y(180);
	add_object(sarah_ptr);
}


