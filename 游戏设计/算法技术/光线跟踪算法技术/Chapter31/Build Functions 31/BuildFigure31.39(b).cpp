// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.39(b)

// The following code is from WrappedThreeColors::get_color:

/*

if (noise < 1.35) {
		return (value * color1);  
	}
	else if (noise < 2.0) {
		return (value * color2);  
	}
	else {
		return (value * color3);   
	}
	
*/

// The threshold values should be built in as data members of WrappedThreeColors

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
	pinhole_ptr->set_view_distance(9600.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr); 
	
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(20, 20, 40);
	light_ptr->scale_radiance(3.0);
	add_light(light_ptr);

	
	// noise:
	
	CubicNoise* noise_ptr = new CubicNoise;	
	noise_ptr->set_num_octaves(6);
	noise_ptr->set_gain(0.5);	
	noise_ptr->set_lacunarity(4.0);		

	// texture:

	WrappedThreeColors* texture_ptr = new WrappedThreeColors(noise_ptr);	
	texture_ptr->set_color1(1.0, 0.8, 0.0);		// gold
	texture_ptr->set_color2(0.7, 1.0, 0.5);		// light green
	texture_ptr->set_color3(0.5, 0.75, 1.0);  	// light blue  
	texture_ptr->set_expansion_number(3.25);	


	// material:
		
	SV_Matte* sv_matte_ptr = new SV_Matte;	 
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.9);
	sv_matte_ptr->set_cd(texture_ptr);
	
	
	Sphere* sphere_ptr = new Sphere(Point3D(0.0), 3.0);
	sphere_ptr->set_material(sv_matte_ptr);
	add_object(sphere_ptr);
}



