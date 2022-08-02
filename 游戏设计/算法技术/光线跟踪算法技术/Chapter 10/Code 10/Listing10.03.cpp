Vector3D
ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const {	
	Point2D p(pixel_point.x * f / d, pixel_point.y * f / d);   // hit point on focal plane
	Vector3D dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - f * w;
	dir.normalize();
	
	return (dir);
}
