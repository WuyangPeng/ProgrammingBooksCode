bool									
AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr) const {			
	float 	t;
	int 	num_objects = sr.w.objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t))
			return (true);  
	
	return (false);  
}
