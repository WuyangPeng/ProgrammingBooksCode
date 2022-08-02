void 												
FishEye::render_scene(World& wr) {
	RGBColour	L;
	ViewPlane	vp(wr.vp);					
	int 		hres		= vp.hres;
	int 		vres 		= vp.vres;
	float		s 			= vp.s;
	Ray			ray;
	int 		depth 		= 0;
	Point2D 	sp; 					// sample point in [0, 1] X [0, 1]
	Point2D 	pp;						// sample point on the pixel
	float		r_squared;				// sum of squares of normalised device coordinates
	
	wr.open_window(vp.hres, vp.vres); 
	ray.o = eye;
		
	for (int r = 0; r < vres; r++)		// up
		for (int c = 0; c < hres; c++) {	// across 					
			L = black; 
						
			for (int j = 0; j < vp.num_samples; j++) {	
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = s * (c - 0.5 * hres + sp.x);
				pp.y = s * (r - 0.5 * vres + sp.y);
				ray.d = ray_direction(pp, hres, vres, s, r_squared);
				
				if (r_squared <= 1.0)
					L += wr.tracer_ptr->trace_ray(ray, depth);
			}
										
			L /= vp.num_samples;	
			L *= exposure_time;	
			wr.display_pixel(r, c, L);
		}
} 
