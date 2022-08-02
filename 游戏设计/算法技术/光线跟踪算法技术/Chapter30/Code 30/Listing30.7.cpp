// Note: One line is different here from Listing 30.7.
// There is no *= operator implemented for multiplying a Point3D by a 
// Matrix on the left.
// The notation below is consistent with Instance.cpp which uses, for example,
// inv_ray.d = inv_matrix * inv_ray.d;


RGBColor
TInstance::get_color(const ShadeRec& sr) const {

	ShadeRec local_sr(sr);
	local_sr.local_hit_point = inv_matrix * local_sr.local_hit_point;
		
	return (texture_ptr->get_color(local_sr));
}
