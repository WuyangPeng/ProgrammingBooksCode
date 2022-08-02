// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 27.20

// The class BeveledBoxShell is like the BeveledBox class, except that it uses part
// spheres and cylinders, instead of the whole objects.
// You will have to implement this an exercise.
// The class BeveledBox is in the code download.
// The class ConvexPartSphere is in the code download.
// You will also have to write the ConvexPartCylinder class as an exercise.

// This scene uses the Dielectric material from Chapter 28, but you can use the
// Transparent material from Chapter 27.

// Render this with different values of max_depth, starting with 1
// Also render it with one ray per pixel, and from different camera locations


void 												
World::build(void) {
	int num_samples = 1;
	
	vp.set_hres(300);	  		
	vp.set_vres(300);
	vp.set_max_depth(5);
	vp.set_samples(num_samples);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.25);
	set_ambient_light(ambient_ptr);
	
	background_color = RGBColor(0.0, 0.3, 0.25);
	
	tracer_ptr = new Whitted(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(10, 7.5, 20);
	pinhole_ptr->set_lookat(0.0);
	pinhole_ptr->set_view_distance(2000.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(20, 20, 15);
	light_ptr->scale_radiance(3.25);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
		
	// beveled box shell	
	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->set_ks(0.5);
	glass_ptr->set_exp(10000.0);
	glass_ptr->set_eta_in(1.5);
	glass_ptr->set_eta_out(1.0);
	glass_ptr->set_cf_in(1.0, 1.0, 0.5);
	
	Point3D p0(-1.0);
	Point3D p1(1.0);
	double bevel_radius = 0.5;

	BeveledBoxShell* box_ptr = new BeveledBoxShell(p0, p1, bevel_radius); 
	box_ptr->set_material(glass_ptr);
	add_object(box_ptr);
	
	
	
	// rectangle
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.0);		
	checker_ptr->set_color1(white);  	
	checker_ptr->set_color2(0.5);
	
	SV_Matte* sv_matte_ptr = new SV_Matte;		
	sv_matte_ptr->set_ka(0.8);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(checker_ptr);
	
	p0 = Point3D(-4.0, -1.01, -4.0);
	Vector3D a(0, 0, 8);
	Vector3D b(8, 0, 0);
	
	Rectangle* rectangle_ptr = new Rectangle(p0, a, b);  
	rectangle_ptr->set_material(sv_matte_ptr);
	add_object(rectangle_ptr);	
}

