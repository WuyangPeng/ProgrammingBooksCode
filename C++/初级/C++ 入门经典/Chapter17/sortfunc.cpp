//DISPLAY 17.2 A Generic Sorting Function
// This is file sortfunc.cpp

template<class T>
void swapValues(T& variable1, T& variable2)
{
      T temp;

      temp = variable1;
      variable1 = variable2;
      variable2 = temp;
}

template<class BaseType>
int indexOfSmallest(const BaseType a[], int startIndex, int numberUsed)
{
    BaseType min = a[startIndex];
    int index_of_min = startIndex;

    for (int index = startIndex + 1; index < numberUsed; index++)
        if (a[index] < min)
        {
            min = a[index];
            index_of_min = index;
            //min is the smallest of a[startIndex] through a[index]
        }

    return index_of_min;
}

template<class BaseType>
void sort(BaseType a[], int numberUsed)
{
int indexOfNextSmallest;
for(int index = 0; index < numberUsed - 1; index++)
   {//Place the correct value in a[index]:
         indexOfNextSmallest =
              indexOfSmallest(a, index, numberUsed);
         swapValues(a[index], a[indexOfNextSmallest]);
      //a[0] <= a[1] <=...<= a[index] are the smallest of the original array
      //elements. The rest of the elements are in the remaining positions.
   }
}

