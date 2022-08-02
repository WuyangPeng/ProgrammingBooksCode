RGBColor								
EnvironmentLight::L(ShadeRec& sr) {
	return (material_ptr->get_Le(sr));
}

// The following function is not in the book.
// It uses Equation 18.6

float									
EnvironmentLight::pdf(ShadeRec& sr) {
	return (sr.normal * wi * invPI);
}


