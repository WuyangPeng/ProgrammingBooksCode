//
// Block.xaml.h
// Declaration of the Block class
//

#pragma once

#include "pch.h"
#include "Block.g.h"

namespace AlphabetBlocks
{
    public ref class Block sealed
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ textProperty;

    public:
        Block();

        static property Windows::UI::Xaml::DependencyProperty^ TextProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        property Platform::String^ Text 
        { 
            Platform::String^ get(); 
            void set(Platform::String^);
        }

        static property int ZIndex
        {
            int get();
        }

    private:
        void OnThumbDragStarted(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::DragStartedEventArgs^ e);
        void OnThumbDragDelta(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::DragDeltaEventArgs^ e);
    };
}
