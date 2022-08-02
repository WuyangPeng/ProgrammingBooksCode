//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Tests whether a sequence of flights exists between two cities.
    Nonrecursive stack version.
 @pre  originCity and destinationCity both exist in the flight map.
 @post  Cities visited during the search are marked as visited
    in the flight map.
 @param originCity  The origin city.
 @param destinationCity  The destination city.
 @return  True if a sequence of flights exists from originCity
    to destinationCity; otherwise returns false. */
bool Map::isPath(City originCity, City destinationCity)
{
   bool success;
   Stack aStack;
   unvisitAll(); // Clear marks on all cities
                 // Push origin city onto aStack and mark it as visited
   aStack.push(originCity);
   markVisited(originCity);
   
   City topCity = aStack.peek();
   while (!aStack.isEmpty() && (topCity != destinationCity))
   {
      // The stack contains a directed path from the origin city
      // at the bottom of the stack to the city at the top of
      // the stack
      
      // Find an unvisited city adjacent to the city on the
      // top of the stack
      City nextCity = getNextCity(topCity, nextCity);
      
      if (nextCity == NO_CITY)
         aStack.pop(); // No city found; backtrack
      else // Visit city
      {
         aStack.push(nextCity);
         markVisited(nextCity);
      } // end if
      
      if (!aStack.isEmpty())
         topCity = aStack.peek();
   } // end while
   
   return !aStack.isEmpty();
} // end isPath