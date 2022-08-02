// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.16

// As this build function does not use the "panoramic" option for the 
// LightProbe mapping, the resulting image is the mirror image of Figure 11.8(b).

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(900);			
	vp.set_vres(900); 
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	
	tracer_ptr = new RayCast(this);	
	
	FishEye* fisheye_ptr = new FishEye;
	fisheye_ptr->set_eye(0.0); 
	fisheye_ptr->set_lookat(0, 0, -100);
	fisheye_ptr->set_fov(360);
	fisheye_ptr->compute_uvw(); 
	set_camera(fisheye_ptr);
	
	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("uffizi_probe_small.ppm");   // development
//	image_ptr->read_ppm_file("uffizi_probe_large.ppm");   // production

	LightProbe* light_probe_ptr = new LightProbe;     	
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(light_probe_ptr);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;	// ka + kd > 1
	sv_matte_ptr->set_ka(1.0);
	sv_matte_ptr->set_kd(0.85); 	
	sv_matte_ptr->set_cd(image_texture_ptr);
	
	Sphere* unit_sphere_ptr = new Sphere;
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* sphere_ptr = new Instance(unit_sphere_ptr); 
	sphere_ptr->scale(1000000.0);
	sphere_ptr->set_material(sv_matte_ptr);
	add_object(sphere_ptr);
}


