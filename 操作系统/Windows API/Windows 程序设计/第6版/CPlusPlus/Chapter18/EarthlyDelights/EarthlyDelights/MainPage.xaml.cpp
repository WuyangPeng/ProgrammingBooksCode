//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#define pi 3.14159

using namespace EarthlyDelights;

using namespace Concurrency;
using namespace DirectX;
using namespace Platform;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

DependencyProperty^ MainPage::interpolationFactorProperty = 
    DependencyProperty::Register("InterpolationFactor", 
                                 TypeName(double::typeid), 
                                 TypeName(MainPage::typeid),
                                 ref new PropertyMetadata(0.0, 
                                 ref new PropertyChangedCallback(OnInterpolationFactorChanged)));

MainPage::MainPage()
{
    InitializeComponent();

    orientationSensor = OrientationSensor::GetDefault();
    DisplayProperties::AutoRotationPreferences = DisplayProperties::NativeOrientation;
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
    SizeChanged += ref new SizeChangedEventHandler(this, &MainPage::OnMainPageSizeChanged);
}

void MainPage::OnTapped(TappedRoutedEventArgs^ args)
{
    // Animate the InterpolationFactor property
    DoubleAnimation^ doubleAnimation = ref new DoubleAnimation();
    doubleAnimation->EnableDependentAnimation = true;
    doubleAnimation->To = double(isZoomView ? 0 : 1);
    TimeSpan timespan = { 10000000 };   // 1 second in 100-nanosecond ticks
    doubleAnimation->Duration = DurationHelper::FromTimeSpan(timespan);

    Storyboard::SetTarget(doubleAnimation, this);
    Storyboard::SetTargetProperty(doubleAnimation, "InterpolationFactor");
    Storyboard^ storyboard = ref new Storyboard();
    storyboard->Children->Append(doubleAnimation);
    storyboard->Begin();
    isZoomView ^= true;
}

void MainPage::OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args)
{
    if (orientationSensor == nullptr)
    {
        MessageDialog^ messageDialog = ref new MessageDialog("OrientationSensor is not avaiable", "Earthly Delights");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([this] (IUICommand^ command) 
        {
            progressBar->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
            statusText->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        });
    }
    else
    {
        bitmapImage->UriSource = 
            ref new Uri("http://upload.wikimedia.org/wikipedia/commons/6/62/The_Garden_of_Earthly_Delights_by_Bosch_High_Resolution_2.jpg");
    }
}

void MainPage::OnMainPageSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    // Save the page dimensions
    pageWidth = this->ActualWidth;
    pageHeight = this->ActualHeight;
    maxDimension = max(pageWidth, pageHeight);

    // Initialize some values
    outlineBorder->Width = pageWidth;
    outlineBorder->Height = pageHeight;
    borderTransform->CenterX = pageWidth / 2;
    borderTransform->CenterY = pageHeight / 2;
}

void MainPage::OnBitmapImageDownloadProgress(Object^ sender, DownloadProgressEventArgs^ args)
{
    progressBar->Value = args->Progress;
}

void MainPage::OnBitmapImageFailed(Object^ sender, ExceptionRoutedEventArgs^ args)
{
    MessageDialog^ messageDialog = ref new MessageDialog("Could not download image: " + args->ErrorMessage, 
                                                         "Earthly Delights");
    task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
    showDialogTask.then([this] (IUICommand^ command) 
    {
        progressBar->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        statusText->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    });
}

void MainPage::OnBitmapImageOpened(Object^ sender, RoutedEventArgs^ args)
{
    progressBar->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    statusText->Visibility = Windows::UI::Xaml::Visibility::Collapsed;

    // Save image dimensions
    imageWidth = bitmapImage->PixelWidth;
    imageHeight = bitmapImage->PixelHeight;

    // Set title text
    wchar_t str[256];
    swprintf(str, sizeof(str) / sizeof(str[0]), 
             L"The Garden of Earthly Delights by Hieronymus Bosch (%i\x00D7%i)", 
             imageWidth, imageHeight);
    titleText->Text = ref new String(str);

    // Initialize image transforms
    zoomInScale = min(pageWidth / imageWidth, pageHeight / imageHeight);

    // Start OrientationSensor going
    if (orientationSensor != nullptr)
    {
        ProcessNewOrientationReading(orientationSensor->GetCurrentReading());
        orientationSensor->ReportInterval = orientationSensor->MinimumReportInterval;
        orientationSensor->ReadingChanged += 
            ref new TypedEventHandler<OrientationSensor^, 
                                      OrientationSensorReadingChangedEventArgs^>(this, &MainPage::OnOrientationSensorReadingChanged);
    }
}

void MainPage::OnOrientationSensorReadingChanged(OrientationSensor^ sender,
                                                 OrientationSensorReadingChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            ProcessNewOrientationReading(args->Reading);
        }));
}

void MainPage::ProcessNewOrientationReading(OrientationSensorReading^ orientationReading)
{
    if (orientationReading == nullptr)
        return;

    // Get the rotation matrix and convert to horizontal coordinates
    SensorRotationMatrix^ m = orientationReading->RotationMatrix;

    if (m == nullptr)
        return;

    XMMATRIX matrix = XMMatrixSet(m->M11, m->M12, m->M13, 0,
                                  m->M21, m->M22, m->M23, 0,
                                  m->M31, m->M32, m->M33, 0,
                                  0, 0, 0, 1);

    // Invert the matrix
    matrix = XMMatrixInverse(nullptr, matrix);

    // Create (0, 0, -1) vector extending from the lens
    XMVECTOR zAxis = XMVectorSet(0, 0, -1, 0);

    // Transform that vector
    XMVECTOR zAxisTransformed = XMVector3Transform(zAxis, matrix);

    // Calculate altitude and azimuth
    double altitude = 180 * asin(XMVectorGetZ(zAxisTransformed)) / pi;
    double azimuth = 180 * atan2(XMVectorGetX(zAxisTransformed), XMVectorGetY(zAxisTransformed)) / pi;

    // Find the theoretical horizontal coordinate for the transformed +Y vector
    //  if the device is upright
    double yUprightAltitude = 0;
    double yUprightAzimuth = 0;

    if (altitude > 0)
    {
        yUprightAltitude = 90 - altitude;
        yUprightAzimuth = 180 + azimuth;
    }
    else
    {
        yUprightAltitude = 90 + altitude;
        yUprightAzimuth = azimuth;
    }

    XMVECTOR yUprightVector = HorizontalCoordinateToVector(yUprightAltitude, yUprightAzimuth);

    // Find the real transform +Y vector
    XMVECTOR yAxis = XMVectorSet(0, 1, 0, 0);
    XMVECTOR yAxisTransformed = XMVector3Transform(yAxis, matrix);

    // Get the angle between the upright +Y vector and the real transform +Y vector
    double dotProduct = XMVectorGetX(XMVector3Dot(yUprightVector, yAxisTransformed));
    XMVECTOR crossProduct = XMVector3Cross(yUprightVector, yAxisTransformed);
    crossProduct = XMVector3Normalize(crossProduct);
    double tilt = 180 * XMVectorGetX(XMVector3Dot(zAxisTransformed, crossProduct)) * acos(dotProduct) / pi;

    // Set the transform center on the Image celement
    imageTransform->CenterX = (imageWidth + maxDimension) *
                                (180 + azimuth) / 360 - maxDimension / 2;
    imageTransform->CenterY = (imageHeight + maxDimension) *
                                (90 - altitude) / 180 - maxDimension / 2;

    // Set the transform on the Border element
    borderTransform->TranslateX = imageTransform->CenterX - pageWidth / 2;
    borderTransform->TranslateY = imageTransform->CenterY - pageHeight / 2;

    // Get rotation from tilt
    rotation = -tilt;
    UpdateImageTransforms();
}

XMVECTOR MainPage::HorizontalCoordinateToVector(double altitude, double azimuth)
{
    altitude *= pi / 180;
    azimuth *= pi / 180;
    double x = cos(altitude) * sin(azimuth);
    double y = cos(altitude) * cos(azimuth);
    double z = sin(altitude);
    return XMVectorSet(float(x), float(y), float(z), 0);
}

void MainPage::OnInterpolationFactorChanged(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    (dynamic_cast<MainPage^>(obj))->UpdateImageTransforms();
}

void MainPage::UpdateImageTransforms()
{
    // If being zoomed out, set scaling
    double interpolatedScale = 1 + InterpolationFactor * (zoomInScale - 1);
    imageTransform->ScaleX = interpolatedScale;
    imageTransform->ScaleY = interpolatedScale;

    // Move transform center to screen center
    imageTransform->TranslateX = pageWidth / 2 - imageTransform->CenterX;
    imageTransform->TranslateY = pageHeight / 2 - imageTransform->CenterY;

    // If being zoomed out, adjust for scaling
    imageTransform->TranslateX -= InterpolationFactor *
                        (pageWidth / 2 - zoomInScale * imageTransform->CenterX);
    imageTransform->TranslateY -= InterpolationFactor *
                        (pageHeight / 2 - zoomInScale * imageTransform->CenterY);

    // If being zoomed out, center Image in screen
    imageTransform->TranslateX += InterpolationFactor *
                        (pageWidth - zoomInScale * imageWidth) / 2;
    imageTransform->TranslateY += InterpolationFactor *
                        (pageHeight - zoomInScale * imageHeight) / 2;

    // Set Border thickness
    outlineBorder->BorderThickness = ThicknessHelper::FromUniformLength(2 / interpolatedScale);
    outlineRectangle->StrokeThickness = 2 / interpolatedScale;

    // Set rotation on Image and Border
    imageTransform->Rotation = (1 - InterpolationFactor) * rotation;
    borderTransform->Rotation = -rotation;
}


