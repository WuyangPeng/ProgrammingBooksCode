#ifndef __LEAVES_H__
#define __LEAVES_H__
//----------------------------------------------------------------------------
//
//leaves.h
//
//Copyright Е Rishi Ramraj, 2004
//Leaf simulation
//----------------------------------------------------------------------------

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Inclusions
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Definitions
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Structures
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

struct link
{
	struct node * neighbour;
	float n_scale;
};

struct node
{
	float energy;
	float scale;

	float pos[3];
	float dir[2];

	link links[3];

	/*struct leaf (*neighbour)[3];
	float n_scale[3];*/
};

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Class Defs
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

class leaves
{
public:
	leaves();
	~leaves();

	bool init(int num_leaves, const float * leaf_pos, const float * wind_dir, float scale_offset, float damp_fac);
	void update(int milliseconds);
	void draw(void (*draw_leaf)(void));
	void add_ripple(int index, float energy);

private:

	bool m_active;

	float wind[2], m_damp_fac;
	
	int m_num_leaves;
	node * m_leaves;
};

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Function Defs
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//----------------------------------------------------------------------------
//leaves.h
//Copyright Е Rishi Ramraj, 2004
//----------------------------------------------------------------------------
#endif //__LEAVES_H__