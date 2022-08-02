RGBColor																	
Checker3D::get_color(const ShadeRec& sr) const {
	
	float eps = -0.000187453738;	// small random number
	float x = sr.local_hit_point.x + eps;
	float y = sr.local_hit_point.y + eps;
	float z = sr.local_hit_point.z + eps;		
	
	if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)	
		return (color1);
	else	
		return (color2);
}
