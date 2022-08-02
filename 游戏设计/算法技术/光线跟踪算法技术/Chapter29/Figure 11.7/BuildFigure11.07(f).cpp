// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 11.7(e)

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	FishEye* fisheye_ptr = new FishEye;
	fisheye_ptr->set_eye(0, 0, 0);     
	fisheye_ptr->set_lookat(0, 1, 0);
	fisheye_ptr->set_fov(180);
	fisheye_ptr->compute_uvw();  
	set_camera(fisheye_ptr);

	
	// skydome with clouds
	
	Image* image_ptr = new Image;						
	image_ptr->read_ppm_file("CloudsHighRes.ppm");	
	
	HemisphericalMap* hemispherical_ptr = new HemisphericalMap; 
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(hemispherical_ptr);
	

	SV_Emissive* sv_emissive_ptr = new SV_Emissive;
	sv_emissive_ptr->set_ce(image_texture_ptr);
	sv_emissive_ptr->scale_radiance(1.0);
	
	Instance* hemisphere_ptr = new Instance(new ConcaveHemisphere); 
	hemisphere_ptr->scale(1000000.0);
	hemisphere_ptr->set_material(sv_emissive_ptr);
	add_object(hemisphere_ptr);
}


