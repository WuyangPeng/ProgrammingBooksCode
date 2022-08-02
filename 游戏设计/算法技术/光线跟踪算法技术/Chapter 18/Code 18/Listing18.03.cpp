RGBColor
Emissive::area_light_shade(ShadeRec& sr) {	
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);
}

