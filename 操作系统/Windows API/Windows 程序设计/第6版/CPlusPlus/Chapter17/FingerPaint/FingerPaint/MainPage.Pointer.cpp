//
// MainPage.Pointer.cpp
// Partial implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FingerPaint;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace PetzoldWindows8VectorDrawing;

void MainPage::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    // Get information from event arguments
    unsigned int id = args->Pointer->PointerId;
    PointerPoint^ pointerPoint = args->GetCurrentPoint(this);

    // Create PointerInfo
    PointerInfo^ pointerInfo = ref new PointerInfo();
    pointerInfo->PreviousPoint = pointerPoint->Position;
    pointerInfo->PreviousRadius = appSettings->Thickness * pointerPoint->Properties->Pressure;

    // Add to dictionary
    pointerDictionary->Insert(id, pointerInfo);

    // Capture the Pointer
    CapturePointer(args->Pointer);
}

void MainPage::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    // Get ID from event arguments
    unsigned int id = args->Pointer->PointerId;

    // If ID is in dictionary, create a new Line element and add to Grid
    if (pointerDictionary->HasKey(id))
    {
        PointerInfo^ pointerInfo = pointerDictionary->Lookup(id);
        IVector<PointerPoint^>^ pointerPoints = args->GetIntermediatePoints(this);

        for (int i = pointerPoints->Size - 1; i >= 0; i--)
        {
            PointerPoint^ pointerPoint = pointerPoints->GetAt(i);

            // For each point, get new position and pressure
            Point point = pointerPoint->Position;
            float radius = appSettings->Thickness * pointerPoint->Properties->Pressure;

            // Render and flag that it's modified
            appSettings->IsImageModified = 
                RenderOnBitmap(pointerInfo->PreviousPoint, pointerInfo->PreviousRadius,
                               point, radius,
                               appSettings->Color);

            // Update PointerInfo 
            pointerInfo->PreviousPoint = point;
            pointerInfo->PreviousRadius = radius;
        }
    }
}

void MainPage::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    // Get ID from event arguments
    unsigned int id = args->Pointer->PointerId;

    // If ID is in dictionary, remove it
    if (pointerDictionary->HasKey(id))
        pointerDictionary->Remove(id);
}

void MainPage::OnPointerCaptureLost(PointerRoutedEventArgs^ args)
{
    // Get ID from event arguments
    unsigned int id = args->Pointer->PointerId;

    // If ID is in dictionary, remove it
    if (pointerDictionary->HasKey(id))
        pointerDictionary->Remove(id);
}

bool MainPage::RenderOnBitmap(Point point1, float radius1, Point point2, float radius2, Color color)
{
    bool bitmapNeedsUpdate = false;

    // Define a line between the two points with rounded caps
    IGeometrySegment^ geoseg = nullptr;

    // Adjust the points for any bitmap scaling
    Point center1 = ScaleToBitmap(point1);
    Point center2 = ScaleToBitmap(point2);

    // Find the distance between them
    double distance = sqrt(pow(center2.X - center1.X, 2) + 
                           pow(center2.Y - center1.Y, 2));

    // Choose the proper way to render the segment
    if (radius1 == radius2)
    {
        geoseg = roundCappedLine;
        roundCappedLine->Set(center1, center2, radius1);
    }
    else if (radius1 < radius2 && radius1 + distance < radius2)
    {
        geoseg = roundCappedLine;
        roundCappedLine->Set(center1, center2, radius2);
    }
    else if (radius2 < radius1 && radius2 + distance < radius1)
    {
        geoseg = roundCappedLine;
        roundCappedLine->Set(center1, center2, radius1);
    }
    else if (radius1 < radius2)
    {
        geoseg = roundCappedPath;
        roundCappedPath->Set(center1, center2, radius1, radius2);
    }
    else
    {
        geoseg = roundCappedPath;
        roundCappedPath->Set(center2, center1, radius2, radius1);
    }

    // Find the minimum and maximum vertical coordinates
    int yMin = (int)min(center1.Y - radius1, center2.Y - radius2);
    int yMax = (int)max(center1.Y + radius1, center2.Y + radius2);

    yMin = max(0, min(bitmap->PixelHeight, yMin));
    yMax = max(0, min(bitmap->PixelHeight, yMax));

    // Loop through all the y coordinates that contain part of that segment
    for (int y = yMin; y < yMax; y++)
    {
        // Get the range of x coordinates in the segment
        xCollection->Clear();
        geoseg->GetAllX(float(y), xCollection);

        if (xCollection->Size == 2)
        {
            // Find the minimum and maximum horizontal coordinates
            int xMin = (int)min(xCollection->GetAt(0), xCollection->GetAt(1) + 0.5f);
            int xMax = (int)max(xCollection->GetAt(0), xCollection->GetAt(1) + 0.5f);

            xMin = max(0, min(bitmap->PixelWidth, xMin));
            xMax = max(0, min(bitmap->PixelWidth, xMax));

            // Loop through the X values
            for (int x = xMin; x < xMax; x++)
            {
                // Set the pixel
                int index = 4 * (y * bitmap->PixelWidth + x);
                pixels[index + 0] = color.B;
                pixels[index + 1] = color.G;
                pixels[index + 2] = color.R;
                pixels[index + 3] = 255;

                bitmapNeedsUpdate = true;
            }
        }
    }

    // Update bitmap
    if (bitmapNeedsUpdate)
        bitmap->Invalidate();

    return bitmapNeedsUpdate;
}

Point MainPage::ScaleToBitmap(Point pt)
{
    return Point((pt.X - imageOffset.X) / imageScale,
                 (pt.Y - imageOffset.Y) / imageScale);
}
