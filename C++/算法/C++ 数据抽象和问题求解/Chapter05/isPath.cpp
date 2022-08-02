//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Tests whether a sequence of flights exists between two cities.
 @pre  originCity and destinationCity both exist in the flight map.
 @post  Cities visited during the search are marked as visited
    in the flight map.
 @param originCity  The origin city.
 @param destinationCity  The destination city.
 @return  True if a sequence of flights exists from originCity
    to destinationCity; otherwise returns false. */
bool Map::isPath(City originCity, City destinationCity)
{
   bool result, done;
   // Mark the current city as visited
   
   markVisited(originCity);
   // Base case: the destination is reached
   if (originCity == destinationCity)
      result = true;
   else // Try a flight to each unvisited city
   {
      done = false;
      City nextCity = getNextCity(originCity);
      while (!done && (nextCity != NO_CITY))
      {
         done = isPath(nextCity, destinationCity);
         if (!done)
            nextCity = getNextCity(originCity);
      } // end while
      
      result = done;
   }  // end if
   
   return result;
}  // end isPath