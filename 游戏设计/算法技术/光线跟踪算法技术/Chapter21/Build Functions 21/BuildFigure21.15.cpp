// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.15.

// Because the ellipsoids' colors and shapes are random (although seeded), you may get 
// different results. That doesn't matter.

void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(400); 
	vp.set_samples(num_samples);	
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 15, 20);
	pinhole_ptr->set_lookat(-0.5, -0.5, 0); 
	pinhole_ptr->set_view_distance(800);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(30, 30, 25);  
	light_ptr->scale_radiance(3.0);  
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// ellipsoids
				
	float 	x0 					= -5.0;					// minimum x center coordinate
	float 	z0 					= -5.0;					// minimum z center coordinate
	float 	x1 					= 5.0;					// maximum x center coordinate
	float 	z1 					= 5.0;					// maximum z center coordinate
	int 	num_x_ellipsoids	= 5;					// number of ellipsoids in the x direction
	int 	num_z_ellipsoids	= 5;  					// number of ellipsoids in the z direction
	float 	radius 				= 1.0;   				// common sphere radius
	float	x_spacing			= (x1 - x0) / (num_x_ellipsoids - 1); // center spacing in x direction
	float	z_spacing			= (z1 - z0) / (num_z_ellipsoids - 1); // center spacing in x direction
	
	Sphere* sphere_ptr = new Sphere;
	set_rand_seed(1000);
	
	for (int iz = 0; iz < num_z_ellipsoids; iz++) {
		for (int ix = 0; ix < num_x_ellipsoids; ix++) {
			Phong* phong_ptr = new Phong;	
			phong_ptr->set_ka(0.35);  
			phong_ptr->set_kd(0.75);
			phong_ptr->set_ks(0.1);  
			phong_ptr->set_exp(20.0);
			phong_ptr->set_cd(rand_float(), rand_float(), rand_float());
			
			float xc = x0 + ix * x_spacing;  	// ellipsoid center x coordinate
			float zc = z0 + iz * z_spacing;		// ellipsoid center z coordinate
			
			Instance* ellipsoid_ptr = new Instance(sphere_ptr);
			ellipsoid_ptr->scale(1.0, 4.0 * rand_float(), 1.0);
			ellipsoid_ptr->translate(xc, 0, zc);
			ellipsoid_ptr->set_material(phong_ptr);
			add_object(ellipsoid_ptr);
		}
	}
	
	// ground plane 
	
	Matte* matte_ptr = new Matte;		
	matte_ptr->set_ka(0.75);
	matte_ptr->set_kd(0.5);
	matte_ptr->set_cd(0.85);  
	
	Plane* plane_ptr = new Plane(Point3D(0, -1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);
}
