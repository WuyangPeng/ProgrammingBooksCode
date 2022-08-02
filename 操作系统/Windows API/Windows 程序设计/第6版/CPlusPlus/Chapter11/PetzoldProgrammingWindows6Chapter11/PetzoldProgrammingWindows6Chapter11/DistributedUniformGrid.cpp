#include "pch.h"
#include "DistributedUniformGrid.h"

using namespace PetzoldProgrammingWindows6Chapter11;

using namespace Windows::Foundation;

DistributedUniformGrid::DistributedUniformGrid()
{
}

Size DistributedUniformGrid::ArrangeOverride(Size finalSize)
{
    unsigned int index = 0;
    float cellWidth = finalSize.Width / cols;
    float cellHeight = finalSize.Height / rows;
    int displayed = 0;

    if (this->Orientation == Windows::UI::Xaml::Controls::Orientation::Vertical)
    {
        for (int row = 0; row < rows; row++)
        {
            float y = row * cellHeight;
            int accumDisplay = (int)ceil((row + 1.0f) * this->Children->Size / rows);
            int display = accumDisplay - displayed;
            cellWidth = (float)(int)(finalSize.Width / display + 0.5f);
            float x = 0;

            for (int col = 0; col < display; col++)
            {
                if (index < this->Children->Size)
                    this->Children->GetAt(index)->Arrange(Rect(x, y, cellWidth, cellHeight));

                x += cellWidth;
                index++;
            }
            displayed += display;
        }
    }
    else
    {
        for (int col = 0; col < cols; col++)
        {
            float x = col * cellWidth;
            int accumDisplay = (int)ceil((col + 1.0f) * this->Children->Size / cols);
            int display = accumDisplay - displayed;
            cellHeight = (float)(int)(finalSize.Height / display + 0.5f);
            float y = 0;

            for (int row = 0; row < display; row++)
            {
                if (index < this->Children->Size)
                    this->Children->GetAt(index)->Arrange(Rect(x, y, cellWidth, cellHeight));

                y += cellHeight;
                index++;
            }
            displayed += display;
        }
    }
    return finalSize;
}


