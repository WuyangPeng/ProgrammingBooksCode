class pvsEngine : public flyEngine
{
public:
	void set_pvs_bit(int node1,int node2);
	int get_pvs_bit(int node1,int node2);
	void build_pvs(int node);
	void sample_node(bsp_node *n,vector& v);
	static_mesh *get_object(bsp_node *n);
	void render_hc_face(vector& p,vector& z,vector& u,char *buf);
	void update_pvs(int node,char *buf);
	void draw_bsp(bsp_node *n,vector& p,vector& z);
	void save_pvslog(char *file);
	int opendata(char *f);
	void save();
	int get_node_random_point(int leafnum,vector& point);
};
