// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.28.

// This is now rendered with a gray background.
// The color is more orange than the original build function,
// which makes the images look more like the printed figures.

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);    
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	background_color = RGBColor(0.5);
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	
	pinhole_ptr->set_eye(0, 0, 100);
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(9500.0); 	
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
	
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(10, 10, 20);		
	light_ptr->scale_radiance(2.5); 
	add_light(light_ptr);
	
	
	// noise:
	
	CubicNoise* noise_ptr = new CubicNoise;
	noise_ptr->set_num_octaves(6); 
	noise_ptr->set_gain(0.5);
	noise_ptr->set_lacunarity(2.0);
	
	// texture:		
	
	TurbulenceTexture* texture_ptr = new TurbulenceTexture(noise_ptr);			
	texture_ptr->set_color(1.0, 0.7, 0.0);  	// orange 			
	texture_ptr->set_min_value(0.0);  			// for Figure 31.28(a)
	texture_ptr->set_max_value(1.2);
//	texture_ptr->set_min_value(0.15);  			// for Figure 31.28(b)
//	texture_ptr->set_max_value(0.75);

	// material:
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(texture_ptr);
	
	// the sphere:
	
	Sphere* sphere_ptr = new Sphere(Point3D(0.0), 3.0); 
	sphere_ptr->set_material(sv_matte_ptr);
	add_object(sphere_ptr);
}



