//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

bool Board::placeQueens(Queen* queenPtr)
{
   // Base case: Try to place a queen in a nonexistent column.
   if (queenPtr->getCol() >= BOARD_SIZE)
   {
      delete queenPtr;
      return true;
   }  // end if
   
   bool isQueenPlaced = false;
   while (!isQueenPlaced && queenPtr->getRow() < BOARD_SIZE)
   {
      // If the queen can be attacked, try moving it
      // to the next row in the current column
      if (queenPtr->isUnderAttack())
         queenPtr->nextRow();
      else
      {
         // Put this queen on the board and try putting a
         // new queen in the first row of the next column
         setQueen(queenPtr);
         Queen* newQueenPtr = new Queen(0, queenPtr->getCol() + 1);
         isQueenPlaced = placeQueens(newQueenPtr);
         
         // If it wasn't possible to put the new queen in the next column,
         // backtrack by deleting the new queen and moving the last
         // queen placed down one row
         if (!isQueenPlaced)
         {
            delete newQueenPtr;
            removeQueen();
            queenPtr->nextRow();
         }  // end if
      }  // end if
   }  // end while
   
   return isQueenPlaced;
}  // end placeQueens