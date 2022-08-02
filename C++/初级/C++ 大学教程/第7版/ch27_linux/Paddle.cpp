// Paddle.cpp
// Paddle class member-function definitions.
#include <Ogre.h> // Ogre class definitions
#include "Paddle.h" // Paddle class definition
using namespace Ogre;

// constructor
Paddle::Paddle( SceneManager *ptr, String paddleName,
   int positionX )
{
   sceneManagerPtr = ptr; // set the pointer to the SceneManager
   name = paddleName; // set the Paddle's name
   x = positionX; // set the Paddle's x coordinate
} // end Paddle constructor

// destructor
Paddle::~Paddle()
{
   // empty body
} // end Paddle default destructor

// add the Paddle to the scene
void Paddle::addToScene()
{
   Entity *entityPtr = sceneManagerPtr->
      createEntity( name, "cube.mesh" ); // create an Entity
   entityPtr->setMaterialName( "paddle" ); // set the Paddle's material
   entityPtr->setNormaliseNormals( true ); // fix the normals when scaled
   nodePtr = sceneManagerPtr->getRootSceneNode()->
      createChildSceneNode( name ); // create a SceneNode for the Paddle
   nodePtr->attachObject( entityPtr ); // attach Paddle to the SceneNode
   nodePtr->setScale( .02, .3, .1 ); // set the Paddle's size
   nodePtr->setPosition( x, 0, 0 ); // set the Paddle's position
} // end function addToScene

// move the Paddle up and down the screen
void Paddle::movePaddle( const Vector3 &direction )
{
   nodePtr->translate( direction ); // move the Paddle
   if ( nodePtr->getPosition().y > 52.5 ) // top of the box
      nodePtr->setPosition( x, 52.5, 0 ); // place Paddle at top of box
   else if ( nodePtr->getPosition().y < -52.5 ) // bottom of the box
      
      // place the Paddle at the bottom of the box
      nodePtr->setPosition( x, -52.5, 0 );
} // end function movePaddle

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

