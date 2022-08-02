void BubbleSortInt( int* array, int size )
{
 int temp;
 int swaps;
 int maxindex = size-1;
 int i;
 do {
  swaps = 0;
  for( i = 0; i < maxindex; i++ ) {
   if( array[i] > array[i+1] ) {
    temp = array[i];
    array[i] = array[i+1];
    array[i+1] = temp;
    swaps++;
   }
  }
  maxindex--;
 } while( swaps != 0 );
}

