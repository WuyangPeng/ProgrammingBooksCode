 /* 'btGame.h' */

 /* Mirus window framework header */
#include "Mirus\Mirus.h"

 /* Breaking Throught header files */
#include "btPaddle.h"
#include "btBall.h"
#include "btBlock.h"

 /* Include this file only once */
#pragma once

 /* Break Through game states */
enum btGameState
{
 btGameRunning           = 1,
 btGameLostBall          = 2,
 btGameLost              = 3,
 btGameSplash            = 4,
 btGameMenu              = 5,
 btGameLevelStarting     = 6,
 btGameLevelComplete     = 7,
 btGameComplete          = 8,
 btGameQuit              = 9,

 btGameStateForceDWord   = 0xFFFFFFFF
};

 /* Break Through game class */
class btGame
{
protected:
  /* Game information */
 btGameState        m_eGameState;
 mrUInt32           m_iBalls;
 mrUInt32           m_iScore;
 mrReal32           m_fTimer;

  /* Game objects */
 btBlock *          m_pkBlocks;
 mrABO *            m_pkBlocksABO;
 mrUInt32           m_iBlocks;
 btPaddle           m_kPaddle;
 btBall             m_kBall;

  /* Paddle controlled by keyboard */
 mrInputManager     m_kInputManager;
 mrKeyboard         m_kKeyboard;

  /* Levels information */
 mrInt8             m_aszLevels [10][256];
 mrUInt32           m_iLevels;
 mrUInt32           m_iCurrentLevel;

  /* Score and ball ABOs */
 mrABO              m_kBallABO;
 mrABO              m_kScore;

  /* Sound members */
 mrSoundPlayer      m_kSoundPlayer;
 mrSound            m_kSoundDie;
 mrSound            m_kSoundBlink;

  /* Background and particle information */
 mrTexture          m_kLightiningTexture;
 mrSurface          m_kBackground;
 mrSurface          m_kSplash;
 mrSurface          m_kGameComplete;
 mrSurface          m_kMainMenu;
 mrEntity           m_kBorder;
 mrABO              m_kReadyGo;

public:
  /* Constructor / Destructor */
 btGame (void);
 ~btGame (void);

 void Start (HINSTANCE hInstance, HWND hWindow);
 void LoadLevel (LPSTR lpszFilename);

  /* Render methods */
 void Render (void);
 void RenderFrame (void);
 void RenderLostBall (void);
 void RenderSplash (void);
 void RenderMenu (void);
 void RenderLevelStarting (void);
 void RenderComplete (void);

  /* Render support methods */
 void RenderBolt (mrUInt32 iRandomness);
 void RenderBlocks ();
 void RenderScoreBalls ();

  /* Handle collisions methods */
 void HandleCollisions (void);
 void HandleCollisionsBlocks (void);
 void HandleCollisionsPaddle (void);
 void HandleCollisionsBorder (void);

  /* Process methods */
 mrBool32 Process (mrReal32 fStep);
 void ProcessFrame (mrReal32 fStep);
 void ProcessLostBall (mrReal32 fStep);
 void ProcessLostGame (mrReal32 fStep);
 void ProcessSplash (mrReal32 fStep);
 void ProcessMenu (mrReal32 fStep);
 void ProcessLevelStarting (mrReal32 fStep);
 void ProcessLevelComplete (mrReal32 fStep);
 void ProcessComplete (mrReal32 fStep);

  /* Game loading methods */
 void LoadGame (void);
 void SaveGame (void);
};