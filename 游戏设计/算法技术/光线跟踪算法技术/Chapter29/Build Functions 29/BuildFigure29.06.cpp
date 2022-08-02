// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This biuilds the scene for Figure 29.6

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400); 
	vp.set_samples(num_samples);
	vp.set_max_depth(0);
	
	background_color = RGBColor(0.5);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(2, 3.5, 5);
	pinhole_ptr->set_lookat(0); 
	pinhole_ptr->set_view_distance(800.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(14, 20, 25);  
	light_ptr->scale_radiance(1.75);  
	light_ptr->set_shadows(true);
	add_light(light_ptr);

	Image* image_ptr = new Image;					
	image_ptr->read_ppm_file("CountryScene.ppm");
	CylindricalMap* map_ptr = new CylindricalMap;   
	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
	texture_ptr->set_mapping(map_ptr);

	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.40);
	sv_matte_ptr->set_kd(0.95);
	sv_matte_ptr->set_cd(texture_ptr);

	OpenCylinder* cylinder_ptr = new OpenCylinder;
	cylinder_ptr->set_material(sv_matte_ptr); 
	add_object(cylinder_ptr);
}