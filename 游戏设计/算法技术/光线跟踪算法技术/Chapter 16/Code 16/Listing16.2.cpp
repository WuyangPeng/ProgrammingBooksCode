bool									
PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int numObjects = sr.w.objects.size();
	float d = location.distance(ray.o);
														
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return (true); 
														
	return (false);     
}
