// Ex9_13.cpp
// Using a nested class to define a stack
#include "Box.h"                    // For CBox and CContainer
#include "GlassBox.h"               // For CGlassBox (and CBox and CContainer)
#include "Stack.h"                  // For the stack class with nested struct CItem 

#include <iostream>                 // For stream I/O

int main()
{
  CBox* pBoxes[] { new CBox{ 2.0, 3.0, 4.0 },
                   new CGlassBox{ 2.0, 3.0, 4.0 },
                   new CBox{ 4.0, 5.0, 6.0 },
                   new CGlassBox{ 4.0, 5.0, 6.0 }
                 };
  std::cout << "The boxes have the following volumes:\n";
  for ( const CBox* pBox : pBoxes)
    pBox->showVolume();                // Output the volume of a box

  std::cout << "\nNow pushing the boxes on the stack...\n\n";
  CStack stack;                        // Create the stack
  for (CBox* pBox : pBoxes)            // Store box pointers in the stack
    stack.push(pBox);

  std::cout << "Popping the boxes off the stack presents them in reverse order:\n";
  CBox* pTemp{};
  while (pTemp = stack.pop())
    pTemp->showVolume();

  for (CBox* pBox : pBoxes)            // Delete the boxes
    delete pBox;
  return 0;
}
