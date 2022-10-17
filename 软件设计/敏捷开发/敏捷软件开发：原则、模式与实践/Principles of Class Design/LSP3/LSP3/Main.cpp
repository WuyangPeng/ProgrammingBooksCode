#include "Square.h"
int main()
{
    Square s;
    s.SetWidth(1);  // Fertunately sets the height to 1 too.
    s.SetHeight(1);  // sets width and height to 2.Good thing.
}

void f(Rectangle& r)
{
    r.SetWidth(32);  // calls Rectangle::SetWidth
}