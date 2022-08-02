#pragma once

namespace ManipulationManagerDemo
{
    public ref class ManipulationManager sealed
    {
    private:
        Windows::UI::Xaml::Media::TransformGroup^ xformGroup;
        Windows::UI::Xaml::Media::MatrixTransform^ matrixXform;
        Windows::UI::Xaml::Media::CompositeTransform^ compositeXform;
        Windows::UI::Xaml::Media::Matrix matrix;

    public:
        ManipulationManager();

        property Windows::UI::Xaml::Media::Matrix Matrix
        {
            Windows::UI::Xaml::Media::Matrix get() { return matrix; }
        }

        void AccumulateDelta(Windows::Foundation::Point point, Windows::UI::Input::ManipulationDelta delta);
    };
}
