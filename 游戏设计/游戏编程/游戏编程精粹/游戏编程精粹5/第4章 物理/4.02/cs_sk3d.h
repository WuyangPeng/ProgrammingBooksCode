#ifndef __CS_SK3D_H__
#define __CS_SK3D_H__
//----------------------------------------------------------------------------
//
//cs_sk3d.h
//
//Copyright Е Rishi Ramraj, 2004
//Skeleton wrapper
//----------------------------------------------------------------------------

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Inclusions
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

#include "cs_sk3d_spec.h"

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Definitions
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Structures
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

typedef struct
{
	int			parent;
	float		relative[16];
}sk3d_joint_t;

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Class Defs
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

class cs_sk3d_c
{
public:

	cs_sk3d_c();
	~cs_sk3d_c();
	
	bool load(char* path);
	void unload(void);
	//delete the absolute matrices
	void del_abs(void);
	
	bool is_active(void) const {return active;}
	//absolutes have not been deleted
	bool has_abs(void) const {return b_abs;}	
	word get_num_jts(void) const {return num_joints;}

	const float * get_abs(const word bone_id) const;
	sk3d_joint_t * get_jnt(const word bone_id) const;
	
private:

	bool active;
	bool b_abs;

	word num_joints;

	sk3d_joint_t	* joints;
	float			* absolutes;
};

//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//
//    header :: Function Defs
//ииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииииии//

//----------------------------------------------------------------------------
//cs_sk3d.h
//Copyright Е Rishi Ramraj, 2004
//----------------------------------------------------------------------------
#endif //__CS_SK3D_H__