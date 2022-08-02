int FindMedianOfThree( int* array, int first, int size )
{
 int last = first+size-1;
 int mid = first+(size/2);
 if( array[first] < array[mid] && array[first] < array[last] ) {
  if( array[mid] < array[last] )
   return mid;
  else
   return last;
 }
 if( array[mid] < array[first] && array[mid] < array[last] ) {
  if( array[first] < array[last] ) 
   return first;
  else
   return last;
 }
 if( array[mid] < array[first] )
  return mid;
 else
  return first;
}

void QuickSortInt( int* array, int min, int size )
{
 int pivot;
 int last = min + size - 1;
 int lower = min;               // lower index holder
 int higher = last;   // upper index holder
 int mid;
 if( size > 1 )
 {
  mid = FindMedianOfThree( array, min, size );
  pivot = array[mid];
  array[mid] = array[min];

  while( lower < higher )
  {
   while( pivot < array[higher] && lower < higher )
    higher--;
   if( higher != lower ) {
    array[lower] = array[higher];
    lower++;
   }
   while( pivot > array[lower] && lower < higher )
    lower++;
   if( higher != lower ) {
    array[higher] = array[lower];
    higher--;
   }
  }
  array[lower] = pivot;
  QuickSortInt( array, min, lower-min );
  QuickSortInt( array, lower+1, last-lower );
 }
}

