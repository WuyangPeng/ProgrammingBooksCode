#include "pch.h"
#include "UniformGridBase.h"

using namespace PetzoldProgrammingWindows6Chapter11;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

DependencyProperty^ UniformGridBase::rowsProperty = 
    DependencyProperty::Register("Rows", 
                                 TypeName(int::typeid), 
                                 TypeName(UniformGridBase::typeid), 
                                 ref new PropertyMetadata(-1, 
                                    ref new PropertyChangedCallback(&UniformGridBase::OnPropertyChanged)));

DependencyProperty^ UniformGridBase::columnsProperty = 
    DependencyProperty::Register("Columns", 
                                 TypeName(int::typeid), 
                                 TypeName(UniformGridBase::typeid), 
                                 ref new PropertyMetadata(-1, 
                                    ref new PropertyChangedCallback(&UniformGridBase::OnPropertyChanged)));

DependencyProperty^ UniformGridBase::orientationProperty = 
    DependencyProperty::Register("Orientation", 
                                 TypeName(int::typeid), 
                                 TypeName(UniformGridBase::typeid), 
                                 ref new PropertyMetadata(Windows::UI::Xaml::Controls::Orientation::Vertical, 
                                    ref new PropertyChangedCallback(&UniformGridBase::OnPropertyChanged)));

void UniformGridBase::OnPropertyChanged(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    if (args->Property == UniformGridBase::OrientationProperty)
    {
        dynamic_cast<UniformGridBase^>(obj)->InvalidateArrange();
    }
    else
    {
        dynamic_cast<UniformGridBase^>(obj)->InvalidateArrange();
    }
}

Size UniformGridBase::MeasureOverride(Size availableSize)
{
    // Only bother if children actually exist
    if (this->Children->Size == 0)
        return Size(0, 0);

    float infinity = std::numeric_limits<float>::infinity();

    // Throw exceptions if the properties aren't OK
    if (this->Rows != -1 && this->Rows < 1)
        throw ref new InvalidArgumentException("UniformGrid Rows must be greater than zero");

    if (this->Columns != -1 && this->Columns < 1)
        throw ref new InvalidArgumentException("UniformGrid Columns must be greater than zero");

    // Determine the actual number of rows and columns
    // -----------------------------------------------
    // This option is discouraged
    if (this->Rows != -1 && this->Columns != -1)
    {
        rows = this->Rows;
        cols = this->Columns;
    }
    // These two options often appear with values of 1
    else if (this->Rows != -1)
    {
        rows = this->Rows;
        cols = (int)ceil((double)this->Children->Size / rows);
    }
    else if (this->Columns != -1)
    {
        cols = this->Columns;
        rows = (int)ceil((double)this->Children->Size / cols);
    }
    // No values yet if both Rows and Columsn are both -1, but
    //      check for infinite availableSize
    else if (availableSize.Width == infinity && availableSize.Height == infinity)
    {
        throw ref new NotImplementedException("Completely unconstrained UniformGrid " +
                                              "requires Rows or Columns property to be set");
    }

    // Determine the maximum size of all children
    // ------------------------------------------
    Size maximumSize(0, 0);
    Size infiniteSize(infinity, infinity);

    // Find the maximum size of all children
    for each (UIElement^ child in this->Children)
    {
        child->Measure(infiniteSize);
        Size childSize = child->DesiredSize;
        maximumSize.Width = max(maximumSize.Width, childSize.Width);
        maximumSize.Height = max(maximumSize.Height, childSize.Height);
    }

    // Find rows and cols if Rows and Columns are both -1
    if (this->Rows == -1 && this->Columns == -1)
    {
        if (availableSize.Width == infinity)
        {
            rows = (int)max(1, availableSize.Height / maximumSize.Height);
            cols = (int)ceil((double)this->Children->Size / rows);
        }
        else if (availableSize.Height == infinity)
        {
            cols = (int)max(1, availableSize.Width / maximumSize.Width);
            rows = (int)ceil((double)this->Children->Size / cols);
        }
        // Neighter dimension is infinite -- the hard one
        else
        {
            float aspectRatio = maximumSize.Width / maximumSize.Height;
            float bestHeight = 0;
            float bestWidth = 0;

            for (unsigned int tryRows = 1; tryRows <= this->Children->Size; tryRows++)
            {
                unsigned int tryCols = (unsigned int)ceil((double)this->Children->Size / tryRows);
                float childHeight = availableSize.Height / tryRows;
                float childWidth = availableSize.Width / tryCols;

                // Adjust for aspect ratio
                if (childWidth > aspectRatio * childHeight)
                    childWidth = aspectRatio * childHeight;
                else
                    childHeight = childWidth / aspectRatio;

                // Check if it's larger than other trials
                if (childHeight > bestHeight)
                {
                    bestHeight = childHeight;
                    bestWidth = childWidth;
                    rows = tryRows;
                    cols = tryCols;
                }
            }
        }
    }
    // Return desired size
    Size desiredSize(min(cols * maximumSize.Width, availableSize.Width),
                     min(rows * maximumSize.Height, availableSize.Height));

    return desiredSize;
}

Size UniformGridBase::ArrangeOverride(Size finalSize)
{
    unsigned int index = 0;
    float cellWidth = finalSize.Width / cols;
    float cellHeight = finalSize.Height / rows;

    if (this->Orientation == Windows::UI::Xaml::Controls::Orientation::Vertical)
    {
        for (int row = 0; row < rows; row++)
        {
            float y = row * cellHeight;

            for (int col = 0; col < cols; col++)
            {
                float x = col * cellWidth;

                if (index < this->Children->Size)
                    this->Children->GetAt(index)->Arrange(Rect(x, y, cellWidth, cellHeight));

                index++;
            }
        }
    }
    else
    {
        for (int col = 0; col < cols; col++)
        {
            float x = col * cellWidth;

            for (int row = 0; row < rows; row++)
            {
                float y = row * cellHeight;

                if (index < this->Children->Size)
                    this->Children->GetAt(index)->Arrange(Rect(x, y, cellWidth, cellHeight));

                index++;
            }
        }
    }
    return Panel::ArrangeOverride(finalSize);
}
