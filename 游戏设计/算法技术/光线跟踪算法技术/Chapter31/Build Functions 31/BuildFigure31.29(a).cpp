// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.29(a)

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
	light_ptr->set_location(5, 5, 20);		
	light_ptr->scale_radiance(6.0);
	add_light(light_ptr);

	
	// noise:
	
	CubicNoise* noise_ptr = new CubicNoise;	
	noise_ptr->set_num_octaves(2);
	noise_ptr->set_gain(0.5);	
	noise_ptr->set_lacunarity(4.0);		

	
	// texture:

	WrappedFBmTexture* texture_ptr = new WrappedFBmTexture(noise_ptr);	
	texture_ptr->set_color(0.3, 0.2, 0.1);   // brown
	texture_ptr->set_expansion_number(10.0);
	texture_ptr->set_min_value(0.0);
	texture_ptr->set_max_value(1.0);
	
	TInstance* scaled_texture_ptr = new TInstance(texture_ptr);
	scaled_texture_ptr->scale(1.0, 4.0, 4.0);


	// material:
		
	SV_Phong* sv_phong_ptr = new SV_Phong;		
	sv_phong_ptr->set_ka(0.5);  
	sv_phong_ptr->set_kd(0.85);
	sv_phong_ptr->set_cd(scaled_texture_ptr);
	sv_phong_ptr->set_ks(0.075);  
	sv_phong_ptr->set_exp(100.0);
	sv_phong_ptr->set_cs(new ConstantColor(white));

	Instance* sphere_ptr = new Instance(new Sphere(Point3D(0.0), 3.0)); 
	sphere_ptr->set_material(sv_phong_ptr);
	sphere_ptr->rotate_y(45);
	add_object(sphere_ptr);
}



