void 												
ThinLens::render_scene(World& w) {
	RGBColour	L;	 	
	Ray			ray;
	ViewPlane	vp(w.vp);
	int 		depth 		= 0;					

	Point2D sp;			// sample point in [0, 1] X [0, 1]
	Point2D pp;			// sample point on a pixel
	Point2D dp; 		// sample point on unit disk
	Point2D lp;			// sample point on lens
	
	w.open_window(vp.hres, vp.vres);
	vp.s /= zoom;  
					
	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 
			L = black;
			
			for (int n = 0; n < vp.num_samples; n++) {
				sp = vp.sampler_ptr->sample_unit_square();			
				pp.x = vp.s * (c - vp.hres / 2.0 + sp.x);
				pp.y = vp.s * (r - vp.vres / 2.0 + sp.y);
				
				dp = sampler_ptr->sample_unit_disk();
				lp = dp * lens_radius;
				
				ray.o = eye + lp.x * u + lp.y * v;
				ray.d = ray_direction(pp, lp);
				L += w.tracer_ptr->trace_ray(ray, depth);
			}
										
			L /= vp.num_samples;
			L *= exposure_time;	
			w.display_pixel(r, c, L);
		}
} 
