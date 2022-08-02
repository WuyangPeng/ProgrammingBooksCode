// Soln9_02.cpp
/*
  It is reasonable to derive a CHawk class from CBird, but not COStrich because an ostrich cannot fly.
  A better hierarchy of classes to represent birds would allow flightless birds such as ostriches and penguins 
  to be represented by a separate class. The hierarchy below allows that.
*/

class CBird
{
protected:
  int wingSpan;
  int eggSize;
};

class CFlightlessBird: public CBird
{
};

class CFlyingBird: public CBird
{
protected:
  int airSpeed;
  int altitude;
public:
  virtual void fly() { altitude = 100; }
};

/*
  Now CHawk can be derived from CFlyingBird and COstrich can be derived from CFlightlessBird
  and the both share the common base class CBird.
*/