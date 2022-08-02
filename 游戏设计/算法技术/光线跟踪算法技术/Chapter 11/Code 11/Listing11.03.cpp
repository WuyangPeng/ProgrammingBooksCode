Vector3D
FishEye::ray_direction(	const Point2D& 	pp, 
						const int 		hres, 
						const int 		vres, 
						const float 	s, 
						float& 			r_squared) const {

	// compute the normalized device coordinates
	
	Point2D pn(2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);	
	r_squared = pn.x * pn.x + pn.y * pn.y;
	
	if (r_squared <= 1.0) {
		float r 		= sqrt(r_squared);
		float psi 		= r * psi_max * PI_ON_180;
		float sin_psi 	= sin(psi);
		float cos_psi 	= cos(psi);
		float sin_alpha = pn.y / r;
		float cos_alpha = pn.x / r;
		Vector3D dir 	= sin_psi * cos_alpha * u +  sin_psi * sin_alpha * v - cos_psi * w;		
				
		return (dir);
	}
	else
		return (Vector3D(0.0));
}
