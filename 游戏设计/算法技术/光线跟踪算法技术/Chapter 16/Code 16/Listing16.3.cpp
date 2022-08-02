bool 												
Plane::shadow_hit(const Ray& ray, float& tmin) const {	
	float t = (a - ray.o) * n / (ray.d * n);
														
	if (t > kEpsilon) {
		tmin = t;
		return (true);	
	}
	else
		return (false);
}
