//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SegoeSymbols;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Shapes;

MainPage::MainPage()
{
    InitializeComponent();
    symbolFont = ref new Windows::UI::Xaml::Media::FontFamily("Segoe UI Symbol");

    for (int row = 0; row < 34; row++)
    {
        RowDefinition^ rowdef = ref new RowDefinition();
        
        if (row == 0 || row % 2 == 1)
            rowdef->Height = GridLengthHelper::Auto;
        else
            rowdef->Height = GridLengthHelper::FromPixels(CellSize);

        characterGrid->RowDefinitions->Append(rowdef);

        if (row != 0 && row % 2 == 0)
        {
            TextBlock^ txtblk = ref new TextBlock();
            txtblk->Text = ToHexString(row / 2 - 1, 1);
            txtblk->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
            Grid::SetRow(txtblk, row);
            Grid::SetColumn(txtblk, 0);
            characterGrid->Children->Append(txtblk);
        }

        if (row % 2 == 1)
        {
            Rectangle^ rectangle = ref new Rectangle();
            rectangle->Stroke = this->Foreground;
            rectangle->StrokeThickness = row == 1 || row == 33 ? 1.5 : 0.5;
            rectangle->Height = 1;
            Grid::SetRow(rectangle, row);
            Grid::SetColumn(rectangle, 0);
            Grid::SetColumnSpan(rectangle, 34);
            characterGrid->Children->Append(rectangle);
        }
    }

    for (int col = 0; col < 34; col++)
    {
        ColumnDefinition^ coldef = ref new ColumnDefinition();

        if (col == 0 || col % 2 == 1)
            coldef->Width = GridLengthHelper::Auto;
        else
            coldef->Width = GridLengthHelper::FromPixels(CellSize);

        characterGrid->ColumnDefinitions->Append(coldef);

        if (col != 0 && col % 2 == 0)
        {
            TextBlock^ txtblk = ref new TextBlock();
            txtblk->Text = "00" + ToHexString(col / 2 - 1, 1) + "_";
            txtblk->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
            Grid::SetRow(txtblk, 0);
            Grid::SetColumn(txtblk, col);
            characterGrid->Children->Append(txtblk);

            txtblkColumnHeads[col / 2 - 1] = txtblk;
        }

        if (col % 2 == 1)
        {
            Rectangle^ rectangle = ref new Rectangle();
            rectangle->Stroke = this->Foreground;
            rectangle->StrokeThickness = col == 1 || col == 33 ? 1.5 : 0.5;
            rectangle->Width = 1;
            Grid::SetRow(rectangle, 0);
            Grid::SetColumn(rectangle, col);
            Grid::SetRowSpan(rectangle, 34);
            characterGrid->Children->Append(rectangle);
        }
    }

    for (int col = 0; col < 16; col++)
        for (int row = 0; row < 16; row++)
        {
            TextBlock^ txtblk = ref new TextBlock();
            txtblk->Text = wchar_t(16 * col + row).ToString();
            txtblk->FontFamily = symbolFont;
            txtblk->FontSize = 24;
            txtblk->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
            txtblk->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
            Grid::SetRow(txtblk, 2 * row + 2);
            Grid::SetColumn(txtblk, 2 * col + 2);
            characterGrid->Children->Append(txtblk);

            txtblkCharacters[row][col] = txtblk;
        }
}

void MainPage::OnSliderValueChanged(Object^ sender, RangeBaseValueChangedEventArgs^ args)
{
    int baseCode = 256 * int(args->NewValue);

    for (int col = 0; col < 16; col++)
    {
        txtblkColumnHeads[col]->Text = ToHexString(baseCode / 16 + col, 3) + "_";

        for (int row = 0; row < 16; row++)
        {
            int code = baseCode + 16 * col + row;
            String^ strChar = nullptr;

            if (code <= 0x0FFFF)
            {
                strChar = wchar_t(code).ToString();
            }
            else
            {
                code -= 0x10000;
                int lead = 0xD800 + code / 1024;
                int trail = 0xDC00 + code % 1024;
                strChar = wchar_t(lead).ToString() + wchar_t(trail).ToString();
            }
            txtblkCharacters[row][col]->Text = strChar;
        }
    }
}

String^ MainPage::ToHexString(int value, int digits)
{
    wchar_t result[16];
    swprintf(result, sizeof(result) / sizeof(result[0]), L"%0*X", digits, value);
    return ref new String(result);
}
