Vector3D
Spherical::ray_direction(	const Point2D& 	pp, 
							const int 		hres, 
							const int 		vres, 
							const float 	s	) const {
	
	// compute the normalised device coordinates
	
	Point2D pn( 2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);
	
	// compute the angles lambda and phi in radians
	
	float lambda 	= pn.x * lambda_max * PI_ON_180;
	float psi 		= pn.y * psi_max * PI_ON_180;
	
	// compute the regular azimuth and polar angles
	
	float phi 		= PI - lambda;
	float theta 	= 0.5 * PI - psi;
	
	float sin_phi 	= sin(phi);
	float cos_phi 	= cos(phi);
	float sin_theta = sin(theta);
	float cos_theta = cos(theta);
	
	Vector3D dir 	= sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w; 

	return (dir);
}
