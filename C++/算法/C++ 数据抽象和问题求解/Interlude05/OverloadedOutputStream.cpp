//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Interlude 5, pp 422.

template<class friendItemType>
ostream& operator<<(ostream& outStream, const LinkedList<friendItemType>& outputList)
{
   int position = 1;
   Node<friendItemType>* currPtr = outputList.headPtr;
   while (currPtr != nullptr)
   {
      outStream << position << "\t" << currPtr->getItem() << endl;
      currPtr = currPtr->getNext();
      position++;
   }
   return outStream;
} // end operator<<