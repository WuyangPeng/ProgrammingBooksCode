// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 15.15

void 												
World::build(void) {
	int num_samples = 1;
	  
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples);  
	
	tracer_ptr = new RayCast(this);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 10000);
	pinhole_ptr->set_lookat(0.0);   
	pinhole_ptr->set_view_distance(15000);	
	pinhole_ptr->compute_uvw(); 
	set_camera(pinhole_ptr);
	
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(100, 100, 200);
	light_ptr->scale_radiance(3.0); 			
	add_light(light_ptr);
	
		
	// colors

	float a = 0.75;  // scaling factor for yellow, orange, and light green
	
	RGBColour yellow(a * 1, a * 1, 0);								// yellow
	RGBColour brown(0.71, 0.40, 0.16);								// brown
	RGBColour dark_green(0.0, 0.41, 0.41);							// dark_green
	RGBColour orange(a * 1, a * 0.75, 0);							// orange
	RGBColour green(0, 0.6, 0.3);									// green
	RGBColour light_green(a * 0.65, a * 1, a * 0.30);				// light green
	RGBColour dark_yellow(0.61, 0.61, 0);							// dark yellow
	RGBColour light_purple(0.65, 0.3, 1);							// light purple
	RGBColour dark_purple(0.5, 0, 1);								// dark purple
	
	
	// Phong materials reflection coefficients
	
	float ka 	= 0.25;
	float kd 	= 0.75;
	float ks 	= 0.1;
	float exp 	= 0.25;
	
	
	// spheres
	
	Phong* phong_ptr1 = new Phong;
	phong_ptr1->set_ka(ka);	
	phong_ptr1->set_kd(kd);
	phong_ptr1->set_ks(ks);
	phong_ptr1->set_exp(exp);
	phong_ptr1->set_cd(yellow);
					
	Sphere*	sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30); 
	sphere_ptr1->set_material(phong_ptr1);	   							// yellow
	add_object(sphere_ptr1);
	
	
	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(ka);	
	phong_ptr2->set_kd(kd);
	phong_ptr2->set_ks(ks);
	phong_ptr2->set_exp(exp);
	phong_ptr2->set_cd(brown);
	
	Sphere*	sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20); 
	sphere_ptr2->set_material(phong_ptr2);								// brown
	add_object(sphere_ptr2);
	

	Phong* phong_ptr3 = new Phong;
	phong_ptr3->set_ka(ka);	
	phong_ptr3->set_kd(kd);
	phong_ptr3->set_ks(ks);
	phong_ptr3->set_exp(exp);
	phong_ptr3->set_cd(dark_green);
		
	Sphere*	sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17); 
	sphere_ptr3->set_material(phong_ptr3);								// dark green
	add_object(sphere_ptr3);
	
	
	Phong* phong_ptr4 = new Phong;
	phong_ptr4->set_ka(ka);	
	phong_ptr4->set_kd(kd);
	phong_ptr4->set_ks(ks);
	phong_ptr4->set_exp(exp);
	phong_ptr4->set_cd(orange);
	
	Sphere*	sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20); 
	sphere_ptr4->set_material(phong_ptr4);								// orange
	add_object(sphere_ptr4);
	
	
	Phong* phong_ptr5 = new Phong;
	phong_ptr5->set_ka(ka);	
	phong_ptr5->set_kd(kd);
	phong_ptr5->set_ks(ks);
	phong_ptr5->set_exp(exp);
	phong_ptr5->set_cd(green);
	
	Sphere*	sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27); 			
	sphere_ptr5->set_material(phong_ptr5);								// green
	add_object(sphere_ptr5);
	
	
	Phong* phong_ptr6 = new Phong;
	phong_ptr6->set_ka(ka);	
	phong_ptr6->set_kd(kd);
	phong_ptr6->set_ks(ks);
	phong_ptr6->set_exp(exp);
	phong_ptr6->set_cd(light_green);
	
	Sphere*	sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25); 
	sphere_ptr6->set_material(phong_ptr6);								// light green
	add_object(sphere_ptr6);
	
	
	Phong* phong_ptr7 = new Phong;
	phong_ptr7->set_ka(ka);	
	phong_ptr7->set_kd(kd);
	phong_ptr7->set_ks(ks);
	phong_ptr7->set_exp(exp);
	phong_ptr7->set_cd(green);
	
	Sphere*	sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22); 
	sphere_ptr7->set_material(phong_ptr7);   							// green
	add_object(sphere_ptr7);
	
	
	Phong* phong_ptr8 = new Phong;
	phong_ptr8->set_ka(ka);	
	phong_ptr8->set_kd(kd);
	phong_ptr8->set_ks(ks);
	phong_ptr8->set_exp(exp);
	phong_ptr8->set_cd(brown);
	
	Sphere*	sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);  
	sphere_ptr8->set_material(phong_ptr8);								// brown
	add_object(sphere_ptr8);
	
	
	Phong* phong_ptr9 = new Phong;
	phong_ptr9->set_ka(ka);	
	phong_ptr9->set_kd(kd);
	phong_ptr9->set_ks(ks);
	phong_ptr9->set_exp(exp);
	phong_ptr9->set_cd(light_green);
	
	Sphere*	sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23); 
	sphere_ptr9->set_material(phong_ptr9);								// light green
	add_object(sphere_ptr9);
	
	
	Phong* phong_ptr10 = new Phong;
	phong_ptr10->set_ka(ka);	
	phong_ptr10->set_kd(kd);
	phong_ptr10->set_ks(ks);
	phong_ptr10->set_exp(exp);
	phong_ptr10->set_cd(dark_green);
			
	Sphere*	sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22); 
	sphere_ptr10->set_material(phong_ptr10);     						// dark green
	add_object(sphere_ptr10);
	
	
	Phong* phong_ptr11 = new Phong;
	phong_ptr11->set_ka(ka);	
	phong_ptr11->set_kd(kd);
	phong_ptr11->set_ks(ks);
	phong_ptr11->set_exp(exp);
	phong_ptr11->set_cd(dark_yellow);
	
	Sphere*	sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22); 
	sphere_ptr11->set_material(phong_ptr11);							// dark yellow
	add_object(sphere_ptr11);
	
	
	Phong* phong_ptr12 = new Phong;
	phong_ptr12->set_ka(ka);	
	phong_ptr12->set_kd(kd);
	phong_ptr12->set_ks(ks);
	phong_ptr12->set_exp(exp);
	phong_ptr12->set_cd(dark_yellow);
	
	Sphere*	sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22); 
	sphere_ptr12->set_material(phong_ptr12);							// dark yellow
	add_object(sphere_ptr12);
	
	
	Phong* phong_ptr13 = new Phong;
	phong_ptr13->set_ka(ka);	
	phong_ptr13->set_kd(kd);
	phong_ptr13->set_ks(ks);
	phong_ptr13->set_exp(exp);
	phong_ptr13->set_cd(dark_yellow);
			
	Sphere*	sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10); 
	sphere_ptr13->set_material(phong_ptr13);
	add_object(sphere_ptr13);											// dark yellow (hidden)
	
	
	Phong* phong_ptr14 = new Phong;
	phong_ptr14->set_ka(ka);	
	phong_ptr14->set_kd(kd);
	phong_ptr14->set_ks(ks);
	phong_ptr14->set_exp(exp);
	phong_ptr14->set_cd(dark_green);
		
	Sphere*	sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18); 
	sphere_ptr14->set_material(phong_ptr14); 							// dark green
	add_object(sphere_ptr14);
	
	
	Phong* phong_ptr15 = new Phong;
	phong_ptr15->set_ka(ka);	
	phong_ptr15->set_kd(kd);
	phong_ptr15->set_ks(ks);
	phong_ptr15->set_exp(exp);
	phong_ptr15->set_cd(brown);
		
	Sphere*	sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18); 
	sphere_ptr15->set_material(phong_ptr15); 							// brown
	add_object(sphere_ptr15);
	
	
	Phong* phong_ptr16 = new Phong;
	phong_ptr16->set_ka(ka);	
	phong_ptr16->set_kd(kd);
	phong_ptr16->set_ks(ks);
	phong_ptr16->set_exp(exp);
	phong_ptr16->set_cd(light_purple);
	
	Sphere*	sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10); 
	sphere_ptr16->set_material(phong_ptr16);							// light purple
	add_object(sphere_ptr16);
	
	
	Phong* phong_ptr17 = new Phong;
	phong_ptr17->set_ka(ka);	
	phong_ptr17->set_kd(kd);
	phong_ptr17->set_ks(ks);
	phong_ptr17->set_exp(exp);
	phong_ptr17->set_cd(brown);
	
	Sphere*	sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15); 		
	sphere_ptr17->set_material(phong_ptr17);							// browm
	add_object(sphere_ptr17);
	
	
	Phong* phong_ptr18 = new Phong;
	phong_ptr18->set_ka(ka);	
	phong_ptr18->set_kd(kd);
	phong_ptr18->set_ks(ks);
	phong_ptr18->set_exp(exp);
	phong_ptr18->set_cd(dark_purple);
	
	Sphere*	sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15); 
	sphere_ptr18->set_material(phong_ptr18);							// dark purple
	add_object(sphere_ptr18);
	
	
	Phong* phong_ptr19 = new Phong;
	phong_ptr19->set_ka(ka);	
	phong_ptr19->set_kd(kd);
	phong_ptr19->set_ks(ks);
	phong_ptr19->set_exp(exp);
	phong_ptr19->set_cd(dark_green);
	
	Sphere*	sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17); 
	sphere_ptr19->set_material(phong_ptr19);							// dark green
	add_object(sphere_ptr19);
	
	
	Phong* phong_ptr20 = new Phong;
	phong_ptr20->set_ka(ka);	
	phong_ptr20->set_kd(kd);
	phong_ptr20->set_ks(ks);
	phong_ptr20->set_exp(exp);
	phong_ptr20->set_cd(brown);

	Sphere*	sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15); 
	sphere_ptr20->set_material(phong_ptr20);							// browm
	add_object(sphere_ptr20);
	
	
	Phong* phong_ptr21 = new Phong;
	phong_ptr21->set_ka(ka);	
	phong_ptr21->set_kd(kd);
	phong_ptr21->set_ks(ks);
	phong_ptr21->set_exp(exp);
	phong_ptr21->set_cd(light_purple);
	 	
	Sphere*	sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10); 
	sphere_ptr21->set_material(phong_ptr21);							// light purple
	add_object(sphere_ptr21);
	
	
	Phong* phong_ptr22 = new Phong;
	phong_ptr22->set_ka(ka);	
	phong_ptr22->set_kd(kd);
	phong_ptr22->set_ks(ks);
	phong_ptr22->set_exp(exp);
	phong_ptr22->set_cd(light_purple);
	
	Sphere*	sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12); 
	sphere_ptr22->set_material(phong_ptr22);							// light purple
	add_object(sphere_ptr22);
	
	
	Phong* phong_ptr23 = new Phong;
	phong_ptr23->set_ka(ka);	
	phong_ptr23->set_kd(kd);
	phong_ptr23->set_ks(ks);
	phong_ptr23->set_exp(exp);
	phong_ptr23->set_cd(dark_purple);
	
	Sphere*	sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13); 			
	sphere_ptr23->set_material(phong_ptr23);							// dark purple
	add_object(sphere_ptr23);	
	
	
	Phong* phong_ptr24 = new Phong;
	phong_ptr24->set_ka(ka);	
	phong_ptr24->set_kd(kd);
	phong_ptr24->set_ks(ks);
	phong_ptr24->set_exp(exp);
	phong_ptr24->set_cd(light_purple);
	 
	Sphere*	sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12); 
	sphere_ptr24->set_material(phong_ptr24);							// light purple
	add_object(sphere_ptr24);
	
	
	Phong* phong_ptr25 = new Phong;
	phong_ptr25->set_ka(ka);	
	phong_ptr25->set_kd(kd);
	phong_ptr25->set_ks(ks);
	phong_ptr25->set_exp(exp);
	phong_ptr25->set_cd(green);
	
	Sphere*	sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11); 			
	sphere_ptr25->set_material(phong_ptr25);					 		// green
	add_object(sphere_ptr25);
	
	
	Phong* phong_ptr26 = new Phong;
	phong_ptr26->set_ka(ka);	
	phong_ptr26->set_kd(kd);
	phong_ptr26->set_ks(ks);
	phong_ptr26->set_exp(exp);
	phong_ptr26->set_cd(light_purple);
	  
	Sphere*	sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12); 		
	sphere_ptr26->set_material(phong_ptr26);							// light purple
	add_object(sphere_ptr26);
	
	
	Phong* phong_ptr27 = new Phong;
	phong_ptr27->set_ka(ka);	
	phong_ptr27->set_kd(kd);
	phong_ptr27->set_ks(ks);
	phong_ptr27->set_exp(exp);
	phong_ptr27->set_cd(light_purple);
	
	Sphere*	sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12); 		
	sphere_ptr27->set_material(phong_ptr27);							// light purple
	add_object(sphere_ptr27);
	
		
	Phong* phong_ptr28 = new Phong;
	phong_ptr28->set_ka(ka);	
	phong_ptr28->set_kd(kd);
	phong_ptr28->set_ks(ks);
	phong_ptr28->set_exp(exp);
	phong_ptr28->set_cd(dark_purple);
	 
	Sphere*	sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15); 
	sphere_ptr28->set_material(phong_ptr28); 							// dark purple
	add_object(sphere_ptr28);
	
	
	
	Phong* phong_ptr29 = new Phong;
	phong_ptr29->set_ka(ka);	
	phong_ptr29->set_kd(kd);
	phong_ptr29->set_ks(ks);
	phong_ptr29->set_exp(exp);
	phong_ptr29->set_cd(dark_purple);
	
	Sphere*	sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15); 
	sphere_ptr29->set_material(phong_ptr29);							// dark purple
	add_object(sphere_ptr29);
	
	
	Phong* phong_ptr30 = new Phong;
	phong_ptr30->set_ka(ka);	
	phong_ptr30->set_kd(kd);
	phong_ptr30->set_ks(ks);
	phong_ptr30->set_exp(exp);
	phong_ptr30->set_cd(dark_purple);
	
	Sphere*	sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);  
	sphere_ptr30->set_material(phong_ptr30); 							// dark purple
	add_object(sphere_ptr30);
	
	
	Phong* phong_ptr31 = new Phong;
	phong_ptr31->set_ka(ka);	
	phong_ptr31->set_kd(kd);
	phong_ptr31->set_ks(ks);
	phong_ptr31->set_exp(exp);
	phong_ptr31->set_cd(light_purple);
	
	Sphere*	sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12); 
	sphere_ptr31->set_material(phong_ptr31); 							// light purple
	add_object(sphere_ptr31);
	
		
	Phong* phong_ptr32 = new Phong;
	phong_ptr32->set_ka(ka);	
	phong_ptr32->set_kd(kd);
	phong_ptr32->set_ks(ks);
	phong_ptr32->set_exp(exp);
	phong_ptr32->set_cd(green);
	
	Sphere*	sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);   
	sphere_ptr32->set_material(phong_ptr32);							//  green
	add_object(sphere_ptr32);
	
	
	Phong* phong_ptr33 = new Phong;
	phong_ptr33->set_ka(ka);	
	phong_ptr33->set_kd(kd);
	phong_ptr33->set_ks(ks);
	phong_ptr33->set_exp(exp);
	phong_ptr33->set_cd(green);
	
	Sphere*	sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11); 
	sphere_ptr33->set_material(phong_ptr33);							// green 
	add_object(sphere_ptr33);
	
	
	Phong* phong_ptr34 = new Phong;
	phong_ptr34->set_ka(ka);	
	phong_ptr34->set_kd(kd);
	phong_ptr34->set_ks(ks);
	phong_ptr34->set_exp(exp);
	phong_ptr34->set_cd(light_purple);
	
	Sphere*	sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10); 	
	sphere_ptr34->set_material(phong_ptr34);							// light purple
	add_object(sphere_ptr34);
	
	
	Phong* phong_ptr35 = new Phong;
	phong_ptr35->set_ka(ka);	
	phong_ptr35->set_kd(kd);
	phong_ptr35->set_ks(ks);
	phong_ptr35->set_exp(exp);
	phong_ptr35->set_cd(light_purple);
	
	Sphere*	sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12); 
	sphere_ptr35->set_material(phong_ptr35);							// light purple
	add_object(sphere_ptr35);
}

