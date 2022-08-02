struct reta
{
	int sizex, sizey;
	int offsetx, offsety, offsetz;
};


class retb
{
public:
	retb();
	virtual ~retb();
	void add(struct reta *r);
	int calc(int max_sx, int max_sy);

private:
	bool arrumar(struct reta *r);
	int procura(int sx, int sy);

	struct reta **l;
	int nl;
};

class lightEngine : public flyEngine
{
public:
	unsigned *gltex;
	int seltex,totlmindx;
	unsigned char *pixel_flags;
	int *lm_flags;

	void mark_used_bsp_faces(bsp_node *n);
	void clear_lightmaps(unsigned char pixel_light);
	static_mesh *get_object(bsp_node *n);
	
	void create_index_lightmaps();
	
	boundbox compute_bbox(int *facelist,int nf);
	int compute_facelist(int facenum,int *facelist);
	int compute_lightmap_uv(boundbox bb,int *facelist,int nf);
	void compute_lightmaps();
	
	void apply_light(bsp_node *n,vector& pos,vector& color,float rad);
	void light(char *f);

	void light_lightmaps();
	void create_lightmaps();

	void sort_faces(bsp_node *n);
};
