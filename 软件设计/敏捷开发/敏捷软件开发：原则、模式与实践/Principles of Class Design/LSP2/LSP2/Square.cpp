#include "Square.h"

void Square::SetWidth(double w)
{
    Rectangle::SetWidth(w);
    Rectangle::SetHeight(w);
}

void Square::SetHeight(double h)
{
    Rectangle::SetWidth(h);
    Rectangle::SetHeight(h);
}
