//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SpinPaint;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();

    inverseRotate = ref new RotateTransform();
    fingerTouches = ref new Map<unsigned int, FingerInfo^>();
    idsInPlay = ref new Vector<unsigned int>();

    Loaded += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ args)
    {
        dimension = (int)min(this->ActualWidth - referencePanel->Margin.Left - referencePanel->Margin.Right,
                             this->ActualHeight - referencePanel->Margin.Top - referencePanel->Margin.Bottom);

        // Create SurfaceImageSource, etc
        OnClearButtonClick(nullptr, nullptr);

        // Initialize transforms
        rotate->CenterX = dimension / 2;
        rotate->CenterY = dimension / 2;

        inverseRotate->CenterX = dimension / 2;
        inverseRotate->CenterY = dimension / 2;

        CompositionTarget::Rendering += ref new EventHandler<Object^>(this, &MainPage::OnCompositionTargetRendering);
    });
}

void MainPage::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;
    Point pt = args->GetCurrentPoint(referencePanel)->Position;

    if (fingerTouches->HasKey(id))
    {
        fingerTouches->Remove(id);
        unsigned int index;
        idsInPlay->IndexOf(id, &index);
        idsInPlay->RemoveAt(index);
    }

    FingerInfo^ fingerInfo = ref new FingerInfo();
    fingerInfo->ThisPosition = pt;
    fingerInfo->LastPosition = Point(-1, -1);
    fingerTouches->Insert(id, fingerInfo);
    idsInPlay->Append(id);
    CapturePointer(args->Pointer);
}

void MainPage::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;
    Point pt = args->GetCurrentPoint(referencePanel)->Position;

    if (fingerTouches->HasKey(id))
        fingerTouches->Lookup(id)->ThisPosition = pt;
}

void MainPage::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;

    if (fingerTouches->HasKey(id))
    {
        fingerTouches->Remove(id);
        unsigned int index;
        idsInPlay->IndexOf(id, &index);
        idsInPlay->RemoveAt(index);
    }
}

void MainPage::OnPointerCaptureLost(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;

    if (fingerTouches->HasKey(id))
    {
        fingerTouches->Remove(id);
        unsigned int index;
        idsInPlay->IndexOf(id, &index);
        idsInPlay->RemoveAt(index);
    }
}

void MainPage::OnCompositionTargetRendering(Object^ sender, Object^ args)
{
    // Get elapsed seconds since app began
    TimeSpan timeSpan = dynamic_cast<RenderingEventArgs^>(args)->RenderingTime;
    double seconds = timeSpan.Duration / 10000000.0;

    // Calculate rotation angle
    rotate->Angle = 360 * seconds / 5;

    // Calculate color and brush
    Color clr;
    seconds = seconds - 10 * (int)(seconds / 10);    // seconds %= 10
    double fraction = 6 * seconds / 10;

    if (fraction < 1)
        clr = ColorHelper::FromArgb(255, 255, (byte)(fraction * 255), 0);
    else if (fraction < 2)
        clr = ColorHelper::FromArgb(255, (byte)(255 - (fraction - 1) * 255), 255, 0);
    else if (fraction < 3)
        clr = ColorHelper::FromArgb(255, 0, 255, (byte)((fraction - 2) * 255));
    else if (fraction < 4)
        clr = ColorHelper::FromArgb(255, 0, (byte)(255 - (fraction - 3) * 255), 255);
    else if (fraction < 5)
        clr = ColorHelper::FromArgb(255, (byte)((fraction - 4) * 255), 0, 255);
    else
        clr = ColorHelper::FromArgb(255, 255, 0, (byte)(255 - (fraction - 5) * 255));

    // This is the WinRTSolidColorBrush
    dynamic_cast<SolidColorBrush^>(pageTitle->Foreground)->Color = clr;

    // All done if nobody's touching
    if (fingerTouches->Size == 0)
        return;

    // Also set color of DirectX solid color brush
    solidColorBrush->SetColor(D2D1::ColorF(clr.R / 255.0f,
                                           clr.G / 255.0f,
                                           clr.B / 255.0f,
                                           clr.A / 255.0f));
    bool bitmapNeedsUpdate = false;
    renderTarget->BeginDraw();

    for each (unsigned int id in idsInPlay)
    {
        FingerInfo^ fingerInfo = fingerTouches->Lookup(id);

        // Find point relative to rotated bitmap
        inverseRotate->Angle = -rotate->Angle;
        Point point1 = inverseRotate->TransformPoint(fingerInfo->ThisPosition);

        if (fingerInfo->LastPosition.X != -1 && fingerInfo->LastPosition.Y != -1)
        {
            Point point2 = fingerInfo->LastPosition;
            float thickness = 12;

            DrawLine(point1, point2, thickness);
            DrawLine(Point(dimension - point1.X, point1.Y), Point(dimension - point2.X, point2.Y), thickness);
            DrawLine(Point(point1.X, dimension - point1.Y), Point(point2.X, dimension - point2.Y), thickness);
            DrawLine(Point(dimension - point1.X, dimension - point1.Y),
                     Point(dimension - point2.X, dimension - point2.Y), thickness);

            bitmapNeedsUpdate = true;
        }
        fingerInfo->LastPosition = point1;
    }

    renderTarget->EndDraw();

    // Update bitmap
    if (bitmapNeedsUpdate)
    {
        surfaceImageSourceRenderer->Update();
    }
}

void MainPage::DrawLine(Point point1, Point point2, float thickness)
{
    D2D1_POINT_2F pt1 = { (float)point1.X, (float)point1.Y };
    D2D1_POINT_2F pt2 = { (float)point2.X, (float)point2.Y };

    renderTarget->DrawLine(pt1, pt2, solidColorBrush.Get(), thickness, strokeStyle.Get());
}

// This method performs initialization during the Loaded event as well.
void MainPage::OnClearButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    SurfaceImageSource^ surfaceImageSource = ref new SurfaceImageSource(dimension, dimension);
    surfaceImageSourceRenderer = ref new SurfaceImageSourceRenderer(surfaceImageSource, dimension, dimension);
    renderTarget = surfaceImageSourceRenderer->RenderTarget;
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0, 0, 1.0f), &solidColorBrush);
    image->Source = surfaceImageSource;

    // Create StrokeStyle for drawing lines
    D2D1_STROKE_STYLE_PROPERTIES strokeStyleProperties = 
    {
        D2D1_CAP_STYLE_ROUND,
        D2D1_CAP_STYLE_ROUND,
        D2D1_CAP_STYLE_ROUND,
        D2D1_LINE_JOIN_ROUND,
        10,
        D2D1_DASH_STYLE_SOLID,
        0
    };

    surfaceImageSourceRenderer->Factory->CreateStrokeStyle(&strokeStyleProperties, nullptr, 0, &strokeStyle);
}
