// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 30.1(a)

// The box with the curved surface cut from it is modeled as follows:
// A CutCube object is defined, which is an axis aligned cube where a hit is only recorded
// when a ray hits the cube AND the hit point is outside a sphere centered on p1 -
// the (+x, +y, +z) vertex.
// You can implement this by starting with an axis aligned box and putting the sphere
// test in the hit and shadow_hit functions, just before they return true.
// I've left this as an exercise.
// The hole is then filled with a concave part sphere.
// If the sphere radius is less than the edge length of the cube, the sphere intersects
// the cube faces at 90 degress, and it's simple to specify the angular ranges - which are
// independent of the radius.
// A more flexible way to render this type of object is with constructive solid
// geometry (CSG), where you just subtract a sphere from a cube.

// The three textures in Figure 30.1 are noise based. The wrapped texture in Figure 30.1(a)
// and the marble texture in Figure 30.1(b) are discussed in Chapter 31. The wood texture in
// Figure 30.1(c) isn't discussed in Chapter 31, but I've included the Wood class and some
// sample images in the Chapter 31 download.

// As I have had to re-render these three images from scatch, the texture's details are 
// different, as are the box, the lighting, and the viewing.



void 												
World::build(void) {
	int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
			
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);    
	set_ambient_light(ambient_ptr);
	
	background_color = RGBColor(black);

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(6, 8, 12);         
	pinhole_ptr->set_lookat(0.0, -0.1, 0.0); 
	pinhole_ptr->set_view_distance(2850.0);  
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(-2, 4, 10);  
	light_ptr->scale_radiance(4.5);   
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	
	
	// wrapped noise texture
	
	// noise
	
	CubicNoise* noise_ptr = new CubicNoise;
	noise_ptr->set_num_octaves(4);
	noise_ptr->set_gain(0.5);	
	noise_ptr->set_lacunarity(2.0);
	
	// texture
	
	WrappedFBmTexture* wrapped_texture_ptr = new WrappedFBmTexture(noise_ptr);	
	wrapped_texture_ptr->set_color(1.0, 0.85, 0.0);   // yellow
	wrapped_texture_ptr->set_expansion_number(10.0);	
	
	TInstance* scaled_texture_ptr = new TInstance(wrapped_texture_ptr);
	scaled_texture_ptr->scale(0.75);
	
	// material:
		
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(scaled_texture_ptr);
	
	
	
	// cut cube parameters
	
	Point3D p0(-1.0);
	Point3D p1(1.0);
	double sphere_radius = 1.5;
	
	CutCube* cut_cube_ptr = new CutCube(p0, p1, sphere_radius); 
	cut_cube_ptr->set_material(sv_matte_ptr);
	add_object(cut_cube_ptr);
	
	
	// concave part sphere parameters
	
	Point3D center(p1);
	double radius 		= sphere_radius;
	double phi_min 		= 180.0;
	double phi_max 		= 270.0;
	double theta_min	= 90.0;
	double theta_max 	= 180.0;
	
	ConcavePartSphere* part_sphere_ptr = new ConcavePartSphere(	center, 
																radius, 
																phi_min, 
																phi_max, 
																theta_min, 
																theta_max);
	part_sphere_ptr->set_material(sv_matte_ptr);
	add_object(part_sphere_ptr);
}


