// Ball.h
// Ball class definition (represents a bouncing ball).
#ifndef BALL_H
#define BALL_H

#include <Ogre.h> // Ogre class definitions
#include <OgreAL.h> // OgreAL class definitions
using namespace Ogre;

class Paddle; // forward declaration of class Paddle

const int RADIUS = 5; // the radius of the Ball

class Ball
{
public:
   Ball( SceneManager *sceneManagerPtr ); // constructor
   ~Ball(); // destructor
   void addToScene(); // add the Ball to the scene
   void moveBall( Real time ); // move the Ball across the screen

private:
   SceneManager *sceneManagerPtr; // pointer to the SceneManager
   SceneNode *nodePtr; // pointer to the SceneNode
   OgreAL::SoundManager *soundManagerPtr; // pointer to the SoundManager
   OgreAL::Sound *wallSoundPtr; // sound played when Ball hits a wall
   OgreAL::Sound *paddleSoundPtr; // sound played when Ball hits a Paddle
   OgreAL::Sound *scoreSoundPtr; // sound played when someone scores
   int speed; // speed of the Ball
   Vector3 direction; // direction of the Ball

   // private utility functions
   void reverseHorizontalDirection(); // change horizontal direction
   void reverseVerticalDirection(); // change vertical direction
   void hitPaddle(); // control the Ball hitting the Paddles
}; // end class Ball

#endif // BALL_H

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

