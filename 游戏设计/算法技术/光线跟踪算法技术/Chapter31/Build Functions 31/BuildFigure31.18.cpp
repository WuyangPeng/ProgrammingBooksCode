// This builds the scene for Figure 31.18

// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// The version of CubicNoise::value_noise in Listing 31.6 was used for this.
// This does not clamp the returned value.

void 												
World::build(void) {
	int num_samples = 9;
	
	vp.set_hres(600);     
	vp.set_vres(600);    
	vp.set_samples(num_samples);
	
	background_color = black;
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 100);
	pinhole_ptr->set_lookat(0.0); 
	pinhole_ptr->set_view_distance(3000.0);         
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
	
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 0, 1);		
	light_ptr->scale_radiance(2.5);
	add_light(light_ptr);
	
	
	// noise:
	
	CubicNoise* noise_ptr = new CubicNoise;		
	noise_ptr->set_num_octaves(1);
	noise_ptr->set_gain(0.5);			// not relevant for one octave
	noise_ptr->set_lacunarity(2.0);		// not relevant for one octave	
	
	// texture:

	FBmTexture* texture_ptr = new FBmTexture(noise_ptr);			
	texture_ptr->set_color(white);  
	texture_ptr->set_min_value(0.0);  
	texture_ptr->set_max_value(1.0);
	
	// material:
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(texture_ptr);
	
	Box* box_ptr1 = new Box(Point3D(-10.0), Point3D(10.0)); 
	box_ptr1->set_material(sv_matte_ptr);
	add_object(box_ptr1);	
}


