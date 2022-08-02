// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 28.38(c)

// This takes a long time to render

void 												
World::build(void) {
	int num_samples = 9;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_max_depth(10);
	
	background_color = RGBColor(0.5);
	
	tracer_ptr = new Whitted(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(5, 6, 10); 
	pinhole_ptr->set_lookat(0, 1, 0); 
	pinhole_ptr->set_view_distance(2000.0);			
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 50, 30); 
	light_ptr1->scale_radiance(3.0);    
	light_ptr1->set_shadows(false);      
	add_light(light_ptr1);


	// materials for the glass of water
	
	// glass-air boundary
	
	RGBColor glass_color(0.65, 1, 0.75);   
	RGBColor water_color(1, 0.25, 1);       
	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_eta_in(1.50);			// glass  
	glass_ptr->set_eta_out(1.0);			// air
	glass_ptr->set_cf_in(glass_color);
	glass_ptr->set_cf_out(white);  
	
	// water-air boundary
	
	Dielectric* water_ptr = new Dielectric;
	water_ptr->set_eta_in(1.33);			// water
	water_ptr->set_eta_out(1.0);			// air
	water_ptr->set_cf_in(water_color);
	water_ptr->set_cf_out(white);

	// water-glass boundary

	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->set_eta_in(1.33); 		// water
	dielectric_ptr->set_eta_out(1.50); 		// glass
	dielectric_ptr->set_cf_in(water_color);
	dielectric_ptr->set_cf_out(glass_color);
	
	
	// Define the GlassOfWater object
	// The parameters below are the default values, but using the constructor that
	// takes these as arguments makes it easier to experiment with different values
	
	double height 			= 2.0;
	double inner_radius 	= 0.9;
	double wall_thickness 	= 0.1;  
	double base_thickness 	= 0.3;
	double water_height 	= 1.5;
	double meniscus_radius 	= 0.1;
	
	GlassOfWater* glass_of_water_ptr = new GlassOfWater(height,
														inner_radius,
														wall_thickness,  
														base_thickness,
														water_height,
														meniscus_radius);
	
	glass_of_water_ptr->set_glass_air_material(glass_ptr);
	glass_of_water_ptr->set_water_air_material(water_ptr);
	glass_of_water_ptr->set_water_glass_material(dielectric_ptr);
	add_object(glass_of_water_ptr);
	
	
	// define the straw
	
	Matte* matte_ptr = new Matte;
	matte_ptr->set_cd(1, 1, 0);  			
	matte_ptr->set_ka(0.25);	
	matte_ptr->set_kd(0.65);
	matte_ptr->set_shadows(false);  // there are no shadows cast on the straw
	
	Instance* straw_ptr = new Instance(new OpenCylinder(-1.2, 1.7, 0.05));
	straw_ptr->set_material(matte_ptr);
	straw_ptr->rotate_z(40);
	straw_ptr->translate(0, 1.25, 0);
	add_object(straw_ptr);
	
	// ground plane

	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(0.5); 
	checker_ptr->set_color1(0.75); 
	checker_ptr->set_color2(white);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.75);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);
}


