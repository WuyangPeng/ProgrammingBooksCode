 /* '12 Player.cpp' */

 /* CPlayer complement header file */
#include "12 Player.h"

 /* Does nothing */
CPlayer::CPlayer ()
{

}

 /* Does nothing */
CPlayer::~CPlayer ()
{

}

 /* Moves player */
void CPlayer::Move (COORD Direction)
{
 m_Position.X += Direction.X;
 m_Position.Y += Direction.Y;
}

 /* Makes leap to random position */
void CPlayer::RandomLeap (COORD ArenaSize)
{
 srand (time (NULL));

 m_Position.X = (rand () % (ArenaSize.X - 1)) + 1;
 m_Position.Y = (rand () % (ArenaSize.Y - 1)) + 1;
}

 /* Gets player position */
void CPlayer::GetPosition (COORD * Position)
{
 memcpy (Position, &m_Position, sizeof (COORD));
}

 /* Sets player lives */
void CPlayer::SetLives (short Lives)
{
 m_Lives = Lives;
}

 /* Gets player lives */
short CPlayer::GetLives (void)
{
 return m_Lives;
}

 /* Sets player score */
void CPlayer::SetScore (int Score)
{
 m_Score = Score;
}

 /* Gets player score */
int CPlayer::GetScore (void)
{
 return m_Score;
}

 /* Sets player available leaps */
void CPlayer::SetLeaps (int Leaps)
{
 m_Leaps = Leaps;
}

 /* Gets player available leaps */
int CPlayer::GetLeaps (void)
{
 return m_Leaps;
}

 /* Sets player position */
void CPlayer::SetPosition (COORD * Position)
{
 m_Position.X = Position->X;
 m_Position.Y = Position->Y;
}/* Print */
