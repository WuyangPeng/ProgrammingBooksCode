// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.40

// The class NestedNoisesTexture is just a wrapped fBm texture class like WrappedTwoColors,
// except that it stores one color and a texture pointer, instead of two colors. As such, it's
// not particularly interesting. 
// A better design would store two texture pointers.
// Here is the get_color function, where wrap_factor is the same as expansion_number.

/*

RGBColor														
NestedNoisesTexture::get_color(const ShadeRec& sr) const {
	float noise = wrap_factor * noise_ptr->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise);
	value = (max_value - min_value) * value + min_value;
	
	if (noise < 1.0)
		return (value * color);
	else
		return (value * texture_ptr->get_color(sr));
}

*/

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
	pinhole_ptr->set_view_distance(9500);  
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
	
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(5, 5, 20);		
	light_ptr2->scale_radiance(3.0);
	add_light(light_ptr2);
	
	
	// noise 1:
	
	CubicNoise* noise_ptr1 = new CubicNoise;	
	noise_ptr1->set_num_octaves(6);
	noise_ptr1->set_gain(0.5);	
	noise_ptr1->set_lacunarity(4.0);		
	
	WrappedTwoColors* texture_ptr = new WrappedTwoColors(noise_ptr1);	
	texture_ptr->set_color1(1.0, 0.8, 0.0);		// gold
	texture_ptr->set_color2(0.5, 0.75, 1.0);  	// light blue  
	texture_ptr->set_expansion_number(2.0);	
	
	TInstance* transformed_wrapped_ptr = new TInstance(texture_ptr);
	transformed_wrapped_ptr->scale(0.25);


	// noise 2:
	
	CubicNoise* noise_ptr2 = new CubicNoise;	
	noise_ptr2->set_num_octaves(3);
	noise_ptr2->set_gain(0.5);	
	noise_ptr2->set_lacunarity(5.0);
	
	
	// nested noises texture:	

	NestedNoisesTexture* nested_textures_ptr = new NestedNoisesTexture(noise_ptr2);	
	nested_textures_ptr->set_color(0.25, 1.0, 0.1);   // bright green		
	nested_textures_ptr->set_texture(transformed_wrapped_ptr);
	nested_textures_ptr->set_min_value(0.0);  
	nested_textures_ptr->set_max_value(1.0);
	nested_textures_ptr->set_wrap_factor(3.0);    

	
	// material:
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.35);
	sv_matte_ptr->set_kd(1.0);
	sv_matte_ptr->set_cd(nested_textures_ptr);

	
	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0), 3); 
	sphere_ptr1->set_material(sv_matte_ptr);
	add_object(sphere_ptr1);
}



