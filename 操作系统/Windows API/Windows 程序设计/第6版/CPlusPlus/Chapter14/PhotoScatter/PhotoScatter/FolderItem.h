#pragma once

#include <stdlib.h>
#include <string.h>

namespace PhotoScatter
{
    [Windows::UI::Xaml::Data::Bindable]
    public ref class FolderItem sealed
    {
     public:
         property Windows::Storage::StorageFolder^ StorageFolder;

        // C++ doesn't support sub-properties in bindings
        property Platform::String^ StorageFolderName
        {
            Platform::String^ get() 
            { 
                return this->StorageFolder == nullptr ? nullptr : this->StorageFolder->Name; 
            }
        }

        property int Level;

        property Platform::String^ Indent
        {
            Platform::String^ get()
            {
                wchar_t* str = (wchar_t*) calloc(this->Level * 4 + 1, sizeof(wchar_t));
                for (int i = 0; i < 4 * this->Level; i++)
                    str[i] = L'\x00A0';

                return ref new Platform::String(str);
            }
        }

        property Windows::UI::Xaml::Controls::Grid^ DisplayGrid;
    };
}
