#ifndef __AST
#define __AST

#include "GameObj.h"

class Ast : public GameObj
{
public:
	//constructors/functions
	Ast(float _size = 1):GameObj(_size)	{Init();}
	virtual void Draw();
	void DoCollision(GameObj *obj);
	void Init();
};
#endif