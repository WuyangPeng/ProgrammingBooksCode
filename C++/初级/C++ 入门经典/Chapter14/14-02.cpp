//DISPLAY 14.2 Iterative Version of the Function in Display 14.1
//Uses iostream:
void writeVertical(int n)
{
    int tensInN = 1;
    int leftEndPiece = n;
    while (leftEndPiece > 9)
    {
        leftEndPiece = leftEndPiece/10;
        tensInN = tensInN*10;
    }
    //tensInN is a power of ten that has the same number
    //of digits as n. For example, if n is 2345, then
    //tensInN is 1000.

    for (int powerOf10 = tensInN;
           powerOf10 > 0; powerOf10 = powerOf10/10)
    {
        cout << (n/powerOf10) << endl;
        n = n%powerOf10;
    }
}


