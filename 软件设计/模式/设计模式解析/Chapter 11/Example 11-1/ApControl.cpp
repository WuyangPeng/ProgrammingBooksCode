#include "ApControl.h"

ApControl::ApControl(void)
{
    // Set myResolution based on configuration
}

ApControl::~ApControl(void)
{
}

void ApControl::void doDraw()
{
    switch (myResolution) 
    {
        case LOW:
            // use lrdd
            break;
        case HIGH:
            // use hrdd
            break;
      }
}

void ApControl::doPrint()
{
    switch (myResolution) 
    {
        case LOW:
            // use lrpd
            break;
        case HIGH:
            // use hrpd
            break;
      }
}