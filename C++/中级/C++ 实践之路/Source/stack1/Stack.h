#if !defined (STACK_H)
#define STACK_H
// (c) Bartosz Milewski 2000

const int maxStack = 16;

class IStack
{
public:
	IStack () :_top (0) {}
	void Push (int i);
	int  Pop ();
private:
	int _arr [maxStack];
	int _top;
};

#endif
