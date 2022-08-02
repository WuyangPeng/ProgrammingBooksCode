Vector3D								
FakeSphericalLight::get_direction(ShadeRec& sr) {

	float r = 3.0;
	Point3D new_location;
	new_location.x = location.x + r * (2.0 * rand_float() - 1.0);
	new_location.y = location.y + r * (2.0 * rand_float() - 1.0);
	new_location.z = location.z + r * (2.0 * rand_float() - 1.0);
	
	return((new_location - sr.hit_point).hat()); 
}
