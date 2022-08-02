bool 	 
Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
		
	double t = (center - ray.o) * normal / (ray.d * normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	if (center.d_squared(p) < r_squared) {
		tmin 				= t;
		sr.normal 			= normal;
		sr.local_hit_point	= p; 
		return (true);	
	}
	else
		return (false);
}
