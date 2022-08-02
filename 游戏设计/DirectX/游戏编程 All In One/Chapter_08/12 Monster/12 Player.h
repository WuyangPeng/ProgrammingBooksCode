 /* '12 Player.h' */

 /* Windows standard header file */
#include <windows.h>
 /* Time header file */
#include <time.h>

 /* Player class */
class CPlayer
{
private:

  /* Player attributes */
 COORD   m_Position;
 short   m_Lives;
 int     m_Score;
 int     m_Leaps;

public:

  /* Constructor / destructor */
 CPlayer ();
 ~CPlayer ();

  /* Move player */
 void Move (COORD Direction);
 void RandomLeap (COORD ArenaSize);

  /* Maintainance methods */
 void GetPosition (COORD * Position);

 void SetLives (short Lives);
 short GetLives (void);

 void SetScore (int Score);
 int GetScore (void);

 void SetLeaps (int Leaps);
 int GetLeaps (void);

 void SetPosition (COORD * Position); /* Print */
};