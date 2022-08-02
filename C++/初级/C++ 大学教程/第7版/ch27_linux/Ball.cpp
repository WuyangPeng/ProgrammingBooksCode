// Ball.cpp
// Ball class member-function definitions.
#include <Ogre.h> // Ogre class definitions
#include <OgreAL.h> // OgreAL class definitions
#include "Ball.h" // Ball class definition
#include "Paddle.h" // Paddle class definition
#include "Pong.h" // Pong class definition
using namespace Ogre;

// Ball constructor
Ball::Ball( SceneManager *ptr )
{
   sceneManagerPtr = ptr; // set pointer to the SceneManager
   soundManagerPtr = new OgreAL::SoundManager(); // create SoundManager
   speed = 100; // speed of the Ball
   direction = Vector3( 1, -1, 0 ); // direction of the Ball
} // end Ball constructor

// Ball destructor
Ball::~Ball()
{
   // empty body
} // end Ball destructor

// add the Ball to the scene
void Ball::addToScene()
{
   // create Entity and attach it to a node in the scene
   Entity *entityPtr = 
      sceneManagerPtr->createEntity( "Ball", "sphere.mesh" );
   entityPtr->setMaterialName( "ball" ); // set material for the Ball
   entityPtr->setNormaliseNormals( true ); // fix the normals when scaled
   nodePtr = sceneManagerPtr->getRootSceneNode()->
      createChildSceneNode( "Ball" ); // create a SceneNode
   nodePtr->attachObject( entityPtr ); // attach the Entity to SceneNode
   nodePtr->setScale( .05, .05, .05 ); // scale SceneNode

   // attach sounds to Ball so they will play from where Ball is
   wallSoundPtr = soundManagerPtr->
      createSound( "wallSound", "wallSound.wav", false );
   nodePtr->attachObject( wallSoundPtr ); // attach a sound to SceneNode
   paddleSoundPtr = soundManagerPtr->
      createSound( "paddleSound", "paddleSound.wav", false );
   nodePtr->attachObject( paddleSoundPtr ); // attach sound to SceneNode
   scoreSoundPtr = soundManagerPtr->
      createSound( "cheer", "cheer.wav", false ); // create a Sound

   // attach the score sound to its own node centered at ( 0, 0, 0 )
   sceneManagerPtr->getRootSceneNode()->createChildSceneNode( "score" )->
      attachObject( scoreSoundPtr );
} // end function addToScene

// move the Ball across the screen
void Ball::moveBall( Real time )
{
   nodePtr->translate( ( direction * ( speed * time ) ) ); // move Ball
   Vector3 position = nodePtr->getPosition(); // get Ball's new position

   // get the positions of the four walls
   Vector3 topPosition = sceneManagerPtr->
      getSceneNode( "WallTop" )->getPosition();
   Vector3 bottomPosition = sceneManagerPtr->
      getSceneNode( "WallBottom" )->getPosition();
   Vector3 leftPosition = sceneManagerPtr->
      getSceneNode( "WallLeft" )->getPosition();
   Vector3 rightPosition = sceneManagerPtr->
      getSceneNode( "WallRight" )->getPosition();

   const int WALL_WIDTH = 5; // the width of the walls

   // check if the Ball hit the left side
   if ( ( position.x  - RADIUS ) <= leftPosition.x + ( WALL_WIDTH / 2 ) ) 
   {
      nodePtr->setPosition( 0, 0, 0 ); // place Ball in center of screen
      Pong::updateScore( PLAYER2 ); // update the score
      scoreSoundPtr->play(); // play a sound when player 2 scores
   } // end if
   // check if the Ball hit the right side
   else if ( 
      ( position.x + RADIUS ) >= rightPosition.x - ( WALL_WIDTH / 2 ) )
   {
      nodePtr->setPosition( 0, 0, 0 ); // place Ball in center of screen
      Pong::updateScore( PLAYER1 ); // update the score
      scoreSoundPtr->play(); // play a sound when player 1 scores
   } // end else
   // check if the Ball hit the bottom wall
   else if ( 
      ( position.y  - RADIUS ) <= bottomPosition.y + ( WALL_WIDTH / 2 ) &&
      direction.y < 0 )
   {
      // place the Ball on the bottom wall
      nodePtr->setPosition( position.x, 
         ( bottomPosition.y + ( WALL_WIDTH / 2 ) + RADIUS ), position.z );
      reverseVerticalDirection(); // make the Ball start moving up
   } // end else
   // check if the Ball hit the top wall
   else if ( 
      ( position.y + RADIUS ) >= topPosition.y - ( WALL_WIDTH / 2 ) &&
      direction.y > 0 )
   {
      // place the Ball on the top wall
      nodePtr->setPosition( position.x, 
         ( topPosition.y - ( WALL_WIDTH / 2 ) - RADIUS ), position.z );
      reverseVerticalDirection(); // make the Ball start moving down
   } // end else

   hitPaddle(); // check if the Ball hit a Paddle
} // end function moveBall

// reverse the Ball's horizontal direction
void Ball::reverseHorizontalDirection()
{
   direction *= Vector3( -1, 1, 1 ); // reverse the horizontal direction
   paddleSoundPtr->play(); // play the "paddleSound" sound effect
} // end function reverseHorizontalDirection

// reverse the Ball's vertical direction
void Ball::reverseVerticalDirection()
{
   direction *= Vector3( 1, -1, 1 ); // reverse the vertical direction
   wallSoundPtr->play(); // play the "wallSound" sound effect
} // end function reverseVerticalDirection

// control the Ball colliding with the Paddle
void Ball::hitPaddle()
{
   // get the position of the Paddles and the Ball
   Vector3 leftPaddlePosition = sceneManagerPtr->
      getSceneNode( "LeftPaddle" )->getPosition(); // left Paddle
   Vector3 rightPaddlePosition = sceneManagerPtr->
      getSceneNode( "RightPaddle" )->getPosition(); // right Paddle
   Vector3 ballPosition = nodePtr->getPosition(); // the Ball's position

   const int PADDLE_WIDTH = 2; // width of the Paddle
   const int PADDLE_HEIGHT = 30; // height of the Paddle

   // is the Ball in range of the left Paddle?
   if ( ( ballPosition.x - RADIUS ) < 
      ( leftPaddlePosition.x + ( PADDLE_WIDTH / 2 ) ) )
   {
      // check for collision with left Paddle
      if ( ( ballPosition.y - RADIUS ) < 
         ( leftPaddlePosition.y + ( PADDLE_HEIGHT / 2 ) ) && 
         ( ballPosition.y + RADIUS ) > 
         ( leftPaddlePosition.y - ( PADDLE_HEIGHT / 2 ) ) )
      {
         reverseHorizontalDirection(); // reverse the Ball's direction

         // place the Ball at the edge of the Paddle
         nodePtr->setPosition( 
            ( leftPaddlePosition.x + ( PADDLE_WIDTH / 2 ) + RADIUS ),
            ballPosition.y, ballPosition.z );
      } // end if
   } // end if
   // is the Ball in range of the right Paddle?
   else if ( ( ballPosition.x + RADIUS ) > 
      ( rightPaddlePosition.x - ( PADDLE_WIDTH / 2 ) ) )
   {
      // check for collision with right Paddle
      if ( ( ballPosition.y - RADIUS ) < 
         ( rightPaddlePosition.y + ( PADDLE_HEIGHT / 2 ) ) &&
         ( ballPosition.y + RADIUS ) > 
         ( rightPaddlePosition.y - ( PADDLE_HEIGHT / 2 ) ) )
      {
         reverseHorizontalDirection(); // reverse the Ball's direction

         // place the Ball at the edge of the Paddle
         nodePtr->setPosition( 
            ( rightPaddlePosition.x - ( PADDLE_WIDTH / 2 ) - RADIUS ), 
            ballPosition.y, ballPosition.z );
      } // end if
   } // end else
} // end function hitPaddle

/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/

