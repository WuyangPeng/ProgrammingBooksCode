 /* 'btGame.cpp' */

 /* Complement header file */
#include "btGame.h"

 /* Default constructor */
btGame::btGame (void)
{
 m_eGameState  = btGameSplash;
 m_fTimer      = 0;
 m_pkBlocks    = NULL;
 m_pkBlocksABO = NULL;
}

 /* Default destructor */
btGame::~btGame (void)
{
 if (m_pkBlocks)
 {
  delete [] m_pkBlocks;
  m_pkBlocks    = NULL;
 }
 if (m_pkBlocksABO)
 {
  delete [] m_pkBlocksABO;
 m_pkBlocksABO = NULL;
 }
 m_eGameState  = btGameSplash;
 m_fTimer      = 0;
}


 /* Start the game */
void btGame::Start (HINSTANCE hInstance, HWND hWindow) 
{
  /* Create the objects */
 m_kPaddle.Create ();
 m_kBall.Create ();

  /* Setup the keyboard for the paddle */
 m_kInputManager.Init (hInstance);
 m_kKeyboard.Init (hWindow);
 
  /* Load support images */
 mrRGBAImage kTempImage;
 kTempImage.LoadFromBitmap ("Graphics/splash.bmp");
 m_kReadyGo.LoadFromFile ("data/readygo.txt");
 m_kReadyGo.SetPosition (320,200);
 m_kReadyGo.SetSize (0,0);
 m_kReadyGo.SetColor (255,255,255,255);
 m_kScore.LoadFromFile ("data/numbers.txt");
 m_kSplash.Create (&kTempImage);
 kTempImage.LoadFromBitmap ("Graphics/complete.bmp");
 m_kGameComplete.Create (&kTempImage);
 kTempImage.LoadFromBitmap ("Graphics/menu.bmp");
 m_kMainMenu.Create (&kTempImage);
 m_kBallABO.LoadFromFile ("data/ball.txt");
 m_kBallABO.SetColor (255,255,255,255);
 m_kBallABO.SetSize (10, 10);
 
  /* Init sound */
 m_kSoundPlayer.Init (hWindow);
 m_kSoundDie.LoadFromFile ("sounds/die.wav");
 m_kSoundBlink.LoadFromFile ("sounds/blink.wav");

  /* Load levels */
 fstream kLevels;
 kLevels.open ("data/levels.txt", ios::in);
 
 if (kLevels.is_open ())
 {
   /* Load number of levels */
  kLevels >> m_iLevels;
  mrUInt32 iLevel;
  
   /* Load each level name */
  for (iLevel=0;iLevel<m_iLevels;iLevel++)
  {
   kLevels >> m_aszLevels [iLevel] ;
  }
  m_iCurrentLevel=0;
 }
 kLevels.close ();
};

 /* Load a level from a file */
void btGame::LoadLevel (LPSTR lpszFilename)
{
 fstream      kLevel;
 
 kLevel.open (lpszFilename, ios::in);

 if (kLevel.is_open ())
 {
  m_kBorder.SetMass (10000000000);
  
   /* Get background name and type */
  mrInt8 aBackgroundName [256];
  kLevel >> aBackgroundName;
  
  mrUInt32 iBackgroundType;
  kLevel >> iBackgroundType;
  
   /* Load the texture image */
  mrRGBAImage kTempImage;
  
  if (1 == iBackgroundType)
  {
   kTempImage.LoadFromBitmap (aBackgroundName);
  }
  if (2 == iBackgroundType)
  {
   kTempImage.LoadFromTarga (aBackgroundName);
  }
  
   /* Create the surface */
  m_kBackground.Create (&kTempImage);
  
   /* Read number of block ABOs */
  mrUInt32 iBlockABOS;
  kLevel >> iBlockABOS;
  
  m_pkBlocksABO = new mrABO [iBlockABOS];
  
   /* For each block, read the block ABO name and load it */
  mrUInt32 iABO;
  for (iABO = 0; iABO < iBlockABOS; iABO++)
  {
   mrInt8 aAboName [256];
   kLevel >> aAboName;
   m_pkBlocksABO [iABO].LoadFromFile (aAboName);
  }
  
  /* Read number of blocks */
  kLevel >> m_iBlocks;
  
  m_pkBlocks = new btBlock [m_iBlocks];
  
  mrUInt32 iBlock;
  
   /* For each block, read the block properties */
  for (iBlock = 0; iBlock < m_iBlocks; iBlock++)
  {
    /* Read ABO ID */
   mrUInt32 iABO;
   kLevel >> iABO;
   
    /* Read block color */
   mrUInt32 iRed;
   kLevel >> iRed;
   mrUInt32 iGreen;
   kLevel >> iGreen;
   mrUInt32 iBlue;
   kLevel >> iBlue;
   mrUInt32 iAlpha;
   kLevel >> iAlpha;
   
    /* Read block position */
   mrReal32 fXPosition;
   kLevel >> fXPosition;
   mrReal32 fYPosition;
   kLevel >> fYPosition; 

    /* Read block size */
   mrUInt32 iWidth;
   kLevel >> iWidth;
   mrUInt32 iHeight;
   kLevel >> iHeight;
   
    /* Create the block */
    /* Set block position */
   mrVector2D kPosition;
   kPosition [0] = fXPosition;
   kPosition [1] = fYPosition;
   m_pkBlocks [iBlock].SetSize (iWidth, iHeight);

   m_pkBlocks [iBlock].Create (iABO, kPosition, (mrUInt8)iRed, 
    (mrUInt8)iGreen, (mrUInt8)iBlue, 
    (mrUInt8)iAlpha);
  }
  kLevel.close ();
 }
}

 /* Render the game */
void btGame::Render (void)
{
  /* Render appropriate state */
 switch (m_eGameState)
 {
 case btGameRunning:
  RenderFrame ();
  break;
 case btGameLostBall:
  RenderLostBall ();
  break;
 case btGameSplash:
  RenderSplash ();
  break;
 case btGameMenu:
  RenderMenu ();
  break;
 case btGameLevelStarting:
  RenderLevelStarting ();
  break;
 case btGameComplete:
  RenderComplete ();
  break;
 }
}

 /* Render the frame */
void btGame::RenderFrame (void)
{
 m_kBackground.Render (NULL);
 RenderBlocks ();
 RenderBolt (10);
 RenderScoreBalls ();
 m_kPaddle.Render ();
 m_kBall.Render ();
}

 /* Render a lost ball */
void btGame::RenderLostBall (void)
{
 m_kBackground.Render (NULL);
 RenderBlocks ();
 RenderBolt (10);
 RenderScoreBalls ();
 m_kPaddle.Render ();
 m_kBall.Render ();
 m_kReadyGo.Render ();
}

 /* Render the splash screen */
void btGame::RenderSplash (void)
{
 m_kSplash.Render (NULL);
}

 /* Render the menu */
void btGame::RenderMenu (void)
{
 m_kMainMenu.Render (NULL);
}

 /* Render the start of a level */
void btGame::RenderLevelStarting (void)
{
 m_kBackground.Render (NULL);
 RenderBlocks ();
 RenderBolt (10);
 RenderScoreBalls ();
 m_kPaddle.Render ();
 m_kBall.Render ();
 m_kReadyGo.Render ();
}

 /* Render game complete */
void btGame::RenderComplete (void)
{
 m_kGameComplete.Render (NULL);
}

 /* Renders the bolt on the bottom of the screen */
void btGame::RenderBolt (mrUInt32 iRandomness)
{
 m_kLightiningTexture.SetActiveTexture ();
 mrVector2D kBoltLines [100];
 
  /* Setup start and final positions */
 kBoltLines [0] [0] = 8;
 kBoltLines [0] [1] = 447;
 kBoltLines [100-1] [0] = 624;
 kBoltLines [100-1] [1] = 447;
 
 mrReal32 fDone;
  /* Percentage done */
 fDone = (kBoltLines [100-1] [0] - kBoltLines [0] [0]) * 1/100;
 
  /* Get a bigger displacement for the first end bolt */
 kBoltLines [1] [0] = kBoltLines [0] [0] + fDone;
 kBoltLines [1] [1] = kBoltLines [0] [1] + iRandomness/2 - 
  (rand () % (iRandomness));
 
  /* Draw first bolt */
 mrScreen::GetSingleton ()->DrawLine (kBoltLines [0][0], 
                                      kBoltLines [0][1], 
                                      kBoltLines [1][0], 
                                      kBoltLines [1][1], 
                                      60, 180, 255, 150);
 
 mrUInt32 iCurrentBolt;
 iCurrentBolt = 2;
 
 while (iCurrentBolt < 100-1)
 {
   /* Percentage done */
  fDone = (kBoltLines [100-1]-kBoltLines [0])[0] * iCurrentBolt / 100;
  
   /* Get a random displacement, and increase the x position by the
      percentage done */
  kBoltLines [iCurrentBolt] [0] = kBoltLines [0][0] + fDone;
  kBoltLines [iCurrentBolt] [1] = kBoltLines [iCurrentBolt - 1] [1] 
           + (1 - (2 * ((mrReal32)rand () / (mrReal32)RAND_MAX))) * 
           0.1f * iRandomness;
  
   /* If too big, clamp it */
  if (fabs (kBoltLines [iCurrentBolt] [1] - kBoltLines [0] [1]) > 
      iRandomness /2)
  {
   kBoltLines [iCurrentBolt] [1] += -(kBoltLines [iCurrentBolt] [1] 
    - kBoltLines [0] [1]) / 2;
  }
  
  /* Draw bolt */
  mrScreen::GetSingleton ()->DrawLine (kBoltLines [iCurrentBolt-1][0], 
                                       kBoltLines [iCurrentBolt-1][1],
                                       kBoltLines [iCurrentBolt][0], 
                                       kBoltLines [iCurrentBolt][1], 
                                       60, 180, 255, 150);
  iCurrentBolt ++;
 }
 
 /* Draw last bolt */
 mrScreen::GetSingleton ()->DrawLine (kBoltLines [iCurrentBolt-1][0],
                                      kBoltLines [iCurrentBolt-1][1],
                                      kBoltLines [100-1][0], 
                                      kBoltLines [100-1][1], 
                                      60, 180, 255, 150);
}

 /* Render the blocks */
void btGame::RenderBlocks ()
{
  /* Render each block */
 mrEntity *  pkBlock;
 mrUInt32    iWidth;
 mrUInt32    iHeight;
 mrVector2D  kPosition;
 mrUInt32    iBlock;
 
 for (iBlock=0; iBlock < m_iBlocks; iBlock++)
 {
   /* Get block proprieties */
  iWidth    = m_pkBlocks [iBlock].GetWidth ();
  iHeight   = m_pkBlocks [iBlock].GetHeight ();
  pkBlock   = m_pkBlocks [iBlock].GetObject ();
  kPosition = pkBlock->GetPosition ();
  
   /* Setup the ABO */
  m_pkBlocksABO [m_pkBlocks [iBlock].GetABO()].SetColor (
   m_pkBlocks [iBlock].GetAlpha (), m_pkBlocks [iBlock].GetRed (), 
   m_pkBlocks [iBlock].GetGreen (), m_pkBlocks [iBlock].GetBlue ());
  m_pkBlocksABO [m_pkBlocks [iBlock].GetABO ()].SetSize (iWidth, iHeight);
  m_pkBlocksABO [m_pkBlocks [iBlock].GetABO ()].SetPosition (
   (mrUInt32)kPosition[0], (mrUInt32)kPosition[1]);
  
   /* Render the ABO */
  m_pkBlocksABO [m_pkBlocks [iBlock].GetABO ()].Render ();
 }
}

 /* Render the score and balls */
void btGame::RenderScoreBalls (void)
{
 mrInt8 szScore [15];
 mrUInt32 iStart;

  /* Convert integer to string */
 itoa (m_iScore, szScore, 10);
 
  /* Render each digit */
 mrUInt32 iDigit;
 m_kScore.SetSize (8,12);
 for (iDigit=0; iDigit < strlen (szScore); iDigit++)
 {
  iStart = 624 - strlen (szScore) * 8;
  m_kScore.SetColor (255,255,225,225);
  m_kScore.SetCurrentAnimation (szScore [iDigit] - 48);
  m_kScore.SetPosition (iStart + iDigit * 8, 8);
  m_kScore.Render ();
 }

  /* Render each ball */
 mrUInt32 iBall;
 for (iBall=0; iBall < m_iBalls; iBall++)
 {
  iStart = 15;
  m_kBallABO.SetColor (255,255,225,225);
  m_kBallABO.SetPosition (iStart + iBall * 12, 8);
  m_kBallABO.Render ();
 }
}

 /* Handle all collisions */
void btGame::HandleCollisions (void)
{
 HandleCollisionsBorder ();
 HandleCollisionsBlocks ();
 HandleCollisionsPaddle ();
}

 /* Handle collision of ball and blocks */
void btGame::HandleCollisionsBlocks (void)
{
 mrEntity * pkBlockEntity;
 mrEntity * pkBallEntity;

 mrUInt32   iBlockWidth;
 mrUInt32   iBlockHeight;
 mrUInt32   iBallRadius;

 mrVector2D kBlockPosition;
 mrVector2D kBallPosition;

  /* Get ball information */
 iBallRadius   = m_kBall.GetSize ();
 pkBallEntity  = m_kBall.GetObject ();
 kBallPosition = pkBallEntity->GetPosition ();

 mrUInt32 iBlock;
 for (iBlock=0; iBlock < m_iBlocks; iBlock++)
 {
   /* If block is active */
  if (m_pkBlocks [iBlock].GetIsAlive () == mrTrue)
  {
    /* Get block proprieties */
   iBlockWidth    = m_pkBlocks [iBlock].GetWidth ();
   iBlockHeight   = m_pkBlocks [iBlock].GetHeight ();
   pkBlockEntity  = m_pkBlocks [iBlock].GetObject ();
   kBlockPosition = pkBlockEntity->GetPosition (); 
 
    /* Test to see if the ball touched the block and if so, 
       destroy the block, add points and play sound */
   if ((kBallPosition [0] >= kBlockPosition [0] - iBlockWidth/2) &&
       (kBallPosition [0] <= kBlockPosition [0] + iBlockWidth/2) &&
       (kBallPosition [1] >= kBlockPosition [1] - iBlockHeight/2) &&
       (kBallPosition [1] <= kBlockPosition [1] + iBlockHeight/2) )
   {
    m_pkBlocks [iBlock].Destroy ();
    m_iScore += 10;
    m_kSoundBlink.Play (mrFalse);
    
     /* Get distance from ball to the all the block sides */
    mrReal32 iX1;
    mrReal32 iY1;
    mrReal32 iX2;
    mrReal32 iY2;

    iX1 = kBlockPosition [0] + iBlockWidth/2 - (kBallPosition [0]-iBallRadius);
    iX2 = kBlockPosition [0] - iBlockWidth/2 - (kBallPosition [0]+iBallRadius);
    iY1 = kBlockPosition [1] + iBlockHeight/2 - (kBallPosition [1]-iBallRadius);
    iY2 = kBlockPosition [1] - iBlockHeight/2 - (kBallPosition [1]+iBallRadius);
     /* Depending on which side of the block the ball hit, handle the collision
        with the appropriate collision plane normal */
    if ( (fabs(iX1) < fabs(iX2)) &&
         (fabs(iX1) < fabs(iY1)) &&
         (fabs(iX1) < fabs(iY2)) )
    {
     pkBallEntity->HandleCollision (*pkBlockEntity, mrVector2D (-1,0));
    }
    if ( (fabs(iX2) < fabs(iY1)) &&
         (fabs(iX2) < fabs(iY2)) )
    {
     pkBallEntity->HandleCollision (*pkBlockEntity, mrVector2D (1,0));
    }
    else if ( fabs(iY1) < fabs(iY2) )
    {
     pkBallEntity->HandleCollision (*pkBlockEntity, mrVector2D (0,-1));
    }
    else
    {
     pkBallEntity->HandleCollision (*pkBlockEntity, mrVector2D (0,1));
    }
   }
  }
 }
}

 /* Handle collisions of paddle with border and paddle with ball */
void btGame::HandleCollisionsPaddle (void)
{
 mrVector2D   kPaddlePosition;
 mrEntity *   kPaddleEntity;
 mrUInt32     iPaddleWidth;
 mrUInt32     iPaddleHeight;

 mrEntity *   pkBallEntity;
 mrVector2D   kBallPosition ;
 mrUInt32     iBallRadius;

  /* Get paddle and ball information */
 iBallRadius     = m_kBall.GetSize ();
 pkBallEntity    = m_kBall.GetObject ();
 kBallPosition   = pkBallEntity->GetPosition ();
 kPaddleEntity   = m_kPaddle.GetObject ();
 kPaddlePosition = kPaddleEntity->GetPosition ();
 iPaddleHeight   = m_kPaddle.GetHeight ();
 iPaddleWidth    = m_kPaddle.GetWidth ()-iPaddleHeight;

  /* Handle collision of ball with paddle */
 if ((kBallPosition [0] + iBallRadius > 
      kPaddlePosition [0] - iPaddleWidth / 2) &&
     (kBallPosition [0] - iBallRadius < 
      kPaddlePosition [0] + iPaddleWidth / 2) &&
     (kBallPosition [1] + iBallRadius > 
      kPaddlePosition [1] - iPaddleHeight / 2) &&
     (kBallPosition [1] + iBallRadius < 
      kPaddlePosition [1] + iPaddleHeight / 2) )
 {
  pkBallEntity->SetPosition (mrVector2D(kBallPosition [0], 
     (kPaddlePosition [1] - iPaddleHeight / 2) - iBallRadius));
  pkBallEntity->HandleCollision (*kPaddleEntity, mrVector2D (0, -1));
  m_kSoundBlink.Play (mrFalse);
 }

  /* Handle collisions of paddle and borders */
 if (kPaddlePosition [0] - m_kPaddle.GetWidth() / 2 < 8)
 {
  kPaddleEntity->SetPosition (mrVector2D (
     (mrReal32)(8 + m_kPaddle.GetWidth()/2),kPaddlePosition [1]));
  kPaddleEntity->HandleCollision (m_kBorder, mrVector2D (1, 0));
 }
 if (kPaddlePosition [0] + m_kPaddle.GetWidth()/2 > 624)
 {
  kPaddleEntity->SetPosition (mrVector2D (
     (mrReal32)(624 - m_kPaddle.GetWidth()/2),kPaddlePosition [1]));
  kPaddleEntity->HandleCollision (m_kBorder, mrVector2D (-1, 0));
 }
}

 /* Handle collisions of ball and border */
void btGame::HandleCollisionsBorder (void)
{
 mrEntity *   pkBallEntity;
 mrVector2D   kBallPosition;
 mrUInt32     iBallRadius;

  /* Get ball information */
 iBallRadius     = m_kBall.GetSize ();
 pkBallEntity    = m_kBall.GetObject ();
 kBallPosition   = pkBallEntity->GetPosition ();

  /* Check if ball hit any of the borders */
 if (kBallPosition [0] + iBallRadius > 624)
 {
  pkBallEntity->SetPosition (mrVector2D ((mrReal32)(624 - iBallRadius),
                                  kBallPosition [1]));
  pkBallEntity->HandleCollision (m_kBorder, mrVector2D (1, 0));
  m_kSoundBlink.Play (mrFalse);
 }
 if (kBallPosition [0] - iBallRadius < 8)
 {
  pkBallEntity->SetPosition (mrVector2D ((mrReal32)(8 + iBallRadius),
                                  kBallPosition [1]));
  pkBallEntity->HandleCollision (m_kBorder, mrVector2D (1, 0));
  m_kSoundBlink.Play (mrFalse);
 }
 if (kBallPosition [1] - iBallRadius < 16)
 {
  pkBallEntity->SetPosition (mrVector2D (kBallPosition [0], 
                                  (mrReal32)(16 + iBallRadius)));
  pkBallEntity->HandleCollision (m_kBorder, mrVector2D (0, 1));
  m_kSoundBlink.Play (mrFalse);
 }
}

 /* Process the game */
mrBool32 btGame::Process (mrReal32 fStep)
{
  /* Process appropriate state */
 switch (m_eGameState)
 {
 case btGameRunning:
  ProcessFrame (fStep);
  break;
 case btGameLostBall:
  ProcessLostBall (fStep);
  break;
 case btGameLost:
  ProcessLostGame (fStep);
  break;
 case btGameSplash:
  ProcessSplash (fStep);
  break;
 case btGameMenu:
  ProcessMenu (fStep);
  break;
 case btGameLevelStarting:
  ProcessLevelStarting (fStep);
  break;
 case btGameLevelComplete:
  ProcessLevelComplete (fStep);
  break;
 case btGameComplete:
  ProcessComplete (fStep);
  break;
 case btGameQuit:
  return mrFalse;
  break;
 }
 return mrTrue;
}

 /* Process the current frame */
void btGame::ProcessFrame (mrReal32 fStep)
{
 
 /* Check if the ball hit the bottom of the screen */
 if ((m_kBall.GetObject ()->GetPosition () [1] >= 443) && 
     (m_kBall.GetIsAlive ()))
 {
  m_kBall.Destroy ();
  m_eGameState = btGameLostBall;
  m_fTimer = 0;
  m_kSoundDie.Play (mrFalse);
 }
 
  /* Check the number of blocks that are alive */
 mrUInt32 iBlock;
 mrUInt32 iBlocksAlive;
 iBlocksAlive = 0;
 for (iBlock=0; iBlock < m_iBlocks; iBlock++)
 {
  if (m_pkBlocks [iBlock].GetIsAlive () == mrTrue)
  {
   iBlocksAlive ++;
  }
 }
  /* If no blocks are alive, level is complete */
 if (iBlocksAlive == 0)
 {
  m_eGameState = btGameLevelComplete;
 }

 mrEntity * pkPaddleEntity;

 pkPaddleEntity = m_kPaddle.GetObject ();
  /* Update the keyboard and see if there are any keys pressed,
     if so, apply the corresponding force to the paddle */
 m_kKeyboard.Update ();
 if (m_kKeyboard.IsButtonDown (DIK_RIGHT))
 {
  pkPaddleEntity->ApplyLinearForce (mrVector2D (4500000, 0));
 }
 if (m_kKeyboard.IsButtonDown (DIK_LEFT))
 {
  pkPaddleEntity->ApplyLinearForce (mrVector2D (-4500000, 0));
 }
  /* Save game */
 if (m_kKeyboard.IsButtonDown (DIK_S))
 {
  SaveGame (); 
 }
  /* Update all the game members */
 HandleCollisions (); 
 m_kPaddle.Update (fStep);
 m_kBall.Update (fStep);
}

 /* Process lost ball */
void btGame::ProcessLostBall (mrReal32 fStep)
{
 m_fTimer += fStep;
 m_kBall.Update (fStep);
  /* If no more balls, game over */
 if (m_iBalls == 0)
 {
   /* Wait a little for ball explosion */
  if (m_fTimer > 1)
  {
   m_eGameState = btGameLost;
  }
 }
  /* Restart playing */
 else
 {
   /* If only one second has passed, show ready */
  if ( (m_fTimer > 1) && (m_fTimer <= 2) )
  {
   m_kReadyGo.SetSize (254, 126);
   m_kReadyGo.SetCurrentAnimation (0);
  }
   /* If only two seconds has passed, show go */
  if ( (m_fTimer > 2) && (m_fTimer <= 3) )
  {
   m_kReadyGo.SetSize (254, 126);
   m_kReadyGo.SetCurrentAnimation (1);
  }
   /* If three seconds has passed, restart game */
  if (m_fTimer > 3)
  {
   m_kReadyGo.SetSize (0, 0);
   m_kBall.Create ();
   m_kPaddle.Create ();
   m_eGameState = btGameRunning;
   m_fTimer     = 0;
   m_iBalls--;
  }
 }
}

 /* Process lost game */
void btGame::ProcessLostGame (mrReal32 fStep)
{
 m_eGameState = btGameMenu;
 m_fTimer     = 0;
}

 /* Process splash screen */
void btGame::ProcessSplash (mrReal32 fStep)
{
  /* Wait three seconds then switch to the main menu */
 m_fTimer += fStep;
 if (m_fTimer <= 3)
 {
 }
 else
 {
  m_eGameState = btGameMenu;
  m_fTimer     = 0;
 }
}

 /* Process menu */
void btGame::ProcessMenu (mrReal32 fStep)
{
 m_kKeyboard.Update ();
  /* If 'N' key was pressed, start a new game */
 if (m_kKeyboard.IsButtonDown (DIK_N))
 {
  m_iCurrentLevel=0;
  LoadLevel (m_aszLevels[m_iCurrentLevel]);
  m_eGameState = btGameLevelStarting;
  m_fTimer     = 0;
  m_iBalls     = 2;
  m_iScore     = 0;
  m_kBall.Create ();
  m_kPaddle.Create ();
 }
  /* If 'N' key was pressed, load a  game */
 if (m_kKeyboard.IsButtonDown (DIK_L))
 {
  LoadGame ();
  LoadLevel (m_aszLevels[m_iCurrentLevel]);
  m_eGameState = btGameLevelStarting;
  m_fTimer     = 0;
  m_kBall.Create ();
  m_kPaddle.Create ();
 }
  /* If 'Q' key was pressed, quit the game */
 if (m_kKeyboard.IsButtonDown (DIK_Q))
 {
  m_eGameState = btGameQuit;
 }
}

 /* Process level starting */
void btGame::ProcessLevelStarting (mrReal32 fStep)
{
 m_fTimer += fStep;

  /* If only one second has passed, show ready */
 if ( (m_fTimer > 1) && (m_fTimer <= 2) )
 {
  m_kReadyGo.SetSize (254, 126);
  m_kReadyGo.SetCurrentAnimation (0);
 }
  /* If only two seconds has passed, show go */
 if ( (m_fTimer > 2) && (m_fTimer <= 3) )
 {
  m_kReadyGo.SetSize (254, 126);
  m_kReadyGo.SetCurrentAnimation (1);
 }
  /* If three seconds has passed, restart game */
 if (m_fTimer > 3)
 {
  m_kReadyGo.SetSize (0, 0);
  m_eGameState = btGameRunning;
  m_fTimer     = 0;
 }
}

 /* Process level complete */
void btGame::ProcessLevelComplete (mrReal32 fStep)
{
 m_iCurrentLevel ++;
  /* Level complete */
 if (m_iCurrentLevel >= m_iLevels)
 {
  m_eGameState = btGameComplete;
 }
  /* Load new level */
 else
 {
  LoadLevel (m_aszLevels [m_iCurrentLevel]);
  m_kBall.Create ();
  m_kPaddle.Create ();
  m_eGameState = btGameLevelStarting;
  m_fTimer = 0;
 }
}

 /* Process game complete */
void btGame::ProcessComplete (mrReal32 fStep)
{
  /* Wait five seconds then switch to the main menu */
 m_fTimer += fStep;
 if (m_fTimer <= 5)
 {
 }
 else
 {
  m_eGameState = btGameMenu;
  m_fTimer = 0;
 }
}

 /* Load a game from file */
void btGame::LoadGame (void)
{
 fstream kGame;
 kGame.open ("game.sav", ios::in);

 if (kGame.is_open ())
 {
   /* Read game data */
  kGame >> m_iBalls;
  kGame >> m_iScore;
  kGame >> m_iCurrentLevel;
 }
 kGame.close ();
}

 /* Save a game to a file */
void btGame::SaveGame (void)
{
 fstream kGame;
 kGame.open ("game.sav", ios::out);

 if (kGame.is_open ())
 {
   /* Save game data */
  kGame << m_iBalls << " ";
  kGame << m_iScore << " ";
  kGame << m_iCurrentLevel << " ";
 }
 kGame.close ();
}

