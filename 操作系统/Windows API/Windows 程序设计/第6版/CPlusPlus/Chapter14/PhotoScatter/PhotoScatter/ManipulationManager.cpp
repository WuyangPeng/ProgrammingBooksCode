#include "pch.h"
#include "ManipulationManager.h"

using namespace PhotoScatter;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;

ManipulationManager::ManipulationManager()
{
    Init(ref new CompositeTransform());
}

ManipulationManager::ManipulationManager(CompositeTransform^ initialTransform)
{
    Init(initialTransform);
}

void ManipulationManager::Init(CompositeTransform^ initialTransform)
{
    xformGroup = ref new TransformGroup();
    matrixXform = ref new MatrixTransform();
    xformGroup->Children->Append(matrixXform);
    compositeXform = initialTransform;
    xformGroup->Children->Append(compositeXform);
    matrix = xformGroup->Value;
}

void ManipulationManager::AccumulateDelta(Point position, ManipulationDelta delta)
{
    matrixXform->Matrix = xformGroup->Value;
    Point center = matrixXform->TransformPoint(position);
    compositeXform->CenterX = center.X;
    compositeXform->CenterY = center.Y;
    compositeXform->TranslateX = delta.Translation.X;
    compositeXform->TranslateY = delta.Translation.Y;
    compositeXform->ScaleX = delta.Scale;
    compositeXform->ScaleY = delta.Scale;
    compositeXform->Rotation = delta.Rotation;
    matrix = xformGroup->Value;
}
