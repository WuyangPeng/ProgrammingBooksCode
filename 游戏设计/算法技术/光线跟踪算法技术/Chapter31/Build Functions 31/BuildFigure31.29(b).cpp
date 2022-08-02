// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.29(b)

void 												
World::build(void) {
	int num_samples = 1;

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
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(5, 5, 20);		
	light_ptr1->scale_radiance(3.0);
	add_light(light_ptr1);

	
	// noise:
	
	CubicNoise* noise_ptr = new CubicNoise;	
	noise_ptr->set_num_octaves(4);
	noise_ptr->set_gain(0.5);	
	noise_ptr->set_lacunarity(2.0);
	
	// texture:

	WrappedFBmTexture* texture_ptr = new WrappedFBmTexture(noise_ptr);	
	texture_ptr->set_color(1.0, 1.0, 0.0);   	// yellow
	texture_ptr->set_expansion_number(10.0);
	texture_ptr->set_min_value(0.0);
	texture_ptr->set_max_value(1.0);
	
	TInstance* scaled_texture_ptr = new TInstance(texture_ptr);
	scaled_texture_ptr->scale(1.5);
	
	
	// material:
		
	SV_Matte* sv_matte_ptr = new SV_Matte;	 
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(scaled_texture_ptr);
	
	
	Sphere* sphere_ptr = new Sphere(Point3D(0.0), 3.0); 
	sphere_ptr->set_material(sv_matte_ptr);
	add_object(sphere_ptr);
}



