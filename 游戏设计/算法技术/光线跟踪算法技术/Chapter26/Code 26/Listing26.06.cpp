RGBColor
Emissive::global_shade(ShadeRec& sr) {	
	if (sr.depth == 1)
		return (black);

	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);
}
