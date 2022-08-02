RGBColor																				
PlaneChecker::get_color(const ShadeRec& sr) const {
	
	float x = sr.local_hit_point.x;
	float z = sr.local_hit_point.z;
	int ix = floor(x / size);
	int iz = floor(z / size);
	float fx = x / size - ix;
	float fz = z / size - iz;
	float width = 0.5 * outline_width / size; 
	bool in_outline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);
	
	if ((ix + iz) % 2 == 0) {
		if (!in_outline)	
			return (color1);
	}
	else {
		if (!in_outline)	
			return (color2);
	}
	
	return (outline_color);
}
