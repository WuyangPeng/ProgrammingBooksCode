//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace NonAffineStretch;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Media3D;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
    imageRect = Rect(0, 0, 320, 400);

    Loaded += ref new RoutedEventHandler([this] (Object^ sender, RoutedEventArgs^ args)
    {
        CalculateNewTransform();
    });
}

void MainPage::OnThumbDragDelta(Object^ sender, DragDeltaEventArgs^ args)
{
    Thumb^ thumb = dynamic_cast<Thumb^>(sender);
    TransformGroup^ xformGroup = dynamic_cast<TransformGroup^>(thumb->RenderTransform);
    TranslateTransform^ translate = dynamic_cast<TranslateTransform^>(xformGroup->Children->GetAt(1));
    translate->X += args->HorizontalChange;
    translate->Y += args->VerticalChange;
    CalculateNewTransform();
}

void MainPage::CalculateNewTransform()
{
    Matrix3D matrix = CalculateNewTransform(imageRect, 
                                            Point((float)ulTranslate->X, (float)ulTranslate->Y),
                                            Point((float)urTranslate->X, (float)urTranslate->Y),
                                            Point((float)llTranslate->X, (float)llTranslate->Y),
                                            Point((float)lrTranslate->X, (float)lrTranslate->Y));
    matrixProjection->ProjectionMatrix = matrix;
}

// The returned transform maps the points (0, 0),
//  (0, 1), (1, 0), and (1, 1) to the points 
//  ptUL, ptUR, ptLL, and ptLR normalized based on rect.
Matrix3D MainPage::CalculateNewTransform(Rect rect, Point ptUL, Point ptUR,
                                                    Point ptLL, Point ptLR)
{
    // Scale and translate normalization transform
    Matrix3D S = Matrix3D::Identity;
    S.M11 = 1 / rect.Width;
    S.M22 = 1 / rect.Height;
    S.OffsetX = -rect.Left / rect.Width;
    S.OffsetY = -rect.Top / rect.Height;
    S.M44 = 1;

    // Affine transform: Maps
    //      (0, 0) --> ptUL
    //      (1, 0) --> ptUR
    //      (0, 1) --> ptLL
    //      (1, 1) --> (x2 + x1 + x0, y2 + y1 + y0)
    Matrix3D A = Matrix3D::Identity;; 
    A.OffsetX = ptUL.X;
    A.OffsetY = ptUL.Y;
    A.M11 = ptUR.X - ptUL.X;
    A.M12 = ptUR.Y - ptUL.Y;
    A.M21 = ptLL.X - ptUL.X;
    A.M22 = ptLL.Y - ptUL.Y;
    A.M44 = 1;

    // Non-Affine transform
    Matrix3D B = Matrix3D::Identity;;
    double den = A.M11 * A.M22 - A.M12 * A.M21;
    double a = (A.M22 * ptLR.X - A.M21 * ptLR.Y +
                        A.M21 * A.OffsetY - A.M22 * A.OffsetX) / den;
    double b = (A.M11 * ptLR.Y - A.M12 * ptLR.X +
                        A.M12 * A.OffsetX - A.M11 * A.OffsetY) / den;

    B.M11 = a / (a + b - 1);
    B.M22 = b / (a + b - 1);
    B.M14 = B.M11 - 1;
    B.M24 = B.M22 - 1;
    B.M44 = 1;

    // Product of three transforms
    return S * B * A;
}
