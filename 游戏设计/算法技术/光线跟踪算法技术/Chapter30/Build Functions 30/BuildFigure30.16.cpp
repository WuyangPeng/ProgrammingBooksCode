// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 30.16 

// You will need to implement the SphereTextures material that allows checkers with two
// different textures to be rendered on a sphere.
// You will also need to implement a spatially varying Phong material. My implementation
// has textures for the diffuse and specular colors. In this figure the specular color is white.
// A slightly simpler implementation would keep the specular color as a RGBColor.

// Note that the RampFBmTexture is constructed using access functions for the parameters.
// Also note that the marble and wood textures are continuous across the checkers.

// Finally, I've changed the background to gray to make it easier to see the sphere.

void 												
World::build(void) {
	int num_samples = 16;

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	background_color = RGBColor(0.5);
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(3, 9, 25); 
	pinhole_ptr->set_lookat(0.0);  
	pinhole_ptr->set_view_distance(7000.0); 
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0.6, 1.1, 1);   
	light_ptr->scale_radiance(3.0);
	add_light(light_ptr);
	
	
	// blue marble ramp image
	
	Image* image_ptr = new Image;						
	image_ptr->read_ppm_file("BlueMarbleRamp.ppm");
	
	
	int 	num_octaves 	= 4;
	float 	lacunarity 		= 2.0;
	float 	gain 			= 0.5;
	float 	perturbation	= 5.0;   // fbm amount
	
	RampFBmTexture* marble_ptr = new RampFBmTexture(image_ptr); 
	marble_ptr->set_num_octaves(num_octaves);
	marble_ptr->set_lacunarity(lacunarity);
	marble_ptr->set_gain(gain);
	marble_ptr->set_perturbation(perturbation);
	
	TInstance* scaled_marble_ptr = new TInstance(marble_ptr);
	scaled_marble_ptr->scale(0.1);
	
	
	// wood

	TInstance* wood_ptr = new TInstance(new Wood(RGBColor(0.5, 0.3, 0.1), black));
	wood_ptr->scale(0.2);
	wood_ptr->rotate_x(45);
	
	
	// texture to hold the marble and wood textures	
	
	SphereTextures* sphere_textures_ptr = new SphereTextures;
	sphere_textures_ptr->set_num_horizontal_checkers(12); 
	sphere_textures_ptr->set_num_vertical_checkers(6);   
	sphere_textures_ptr->set_texture1(scaled_marble_ptr);
	sphere_textures_ptr->set_texture2(wood_ptr);
	
	
	// spatially varying Phong material	
		
	SV_Phong* sv_phong_ptr = new SV_Phong;		
	sv_phong_ptr->set_ka(0.25);  
	sv_phong_ptr->set_kd(0.75);
	sv_phong_ptr->set_cd(sphere_textures_ptr);
	sv_phong_ptr->set_ks(0.25);  
	sv_phong_ptr->set_exp(20.0);
	sv_phong_ptr->set_cs(new ConstantColor(white));
	
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_material(sv_phong_ptr);
	add_object(sphere_ptr);
}


