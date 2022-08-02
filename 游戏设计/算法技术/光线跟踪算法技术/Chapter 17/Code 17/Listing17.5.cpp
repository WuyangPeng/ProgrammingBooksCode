RGBColor
AmbientOccluder::L(ShadeRec& sr) {	
	w = sr.normal;	
	v = w ^ Vector3D(0.0072, 1.0, 0.0034); // jitter the up vector in case normal is vertical
	v.normalise();
	u = v ^ w;
	
	Ray shadow_ray;
	shadow_ray.o = sr.hit_point;
	shadow_ray.d = get_direction(sr);  
	
	if (in_shadow(shadow_ray, sr))
		return (min_amount * ls * color);
	else	
		return (ls * color);
}
