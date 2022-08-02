class ThinLens: public Camera {

	public:
	
		// constructors, access functions, etc
		
		void
		set_sampler(Sampler* sp);	
		
		Vector3D
		ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;
		
		virtual void 												
		render_scene(World& w);
			
	private:
	
		float		lens_radius;	// lens radius
		float		d;				// view plane distance
		float		f;				// focal distance
		float		zoom;			// zoom factor
		Sampler*	sampler_ptr;	// sampler object
};
