#pragma once
namespace MemoryTest
{
  public ref class Card sealed
  {
  public:
    Card() {}

    // Copy constructor 
    Card(Card^ card)
    {
      Type = card->Type;
      Color = card->Color;
      Shape = card->Shape;
      Back = card->Back;
    }

  public:
    property Platform::String^ Type;                           // Shape type
    property Windows::UI::Xaml::Media::SolidColorBrush^ Color; // Color
    property Windows::UI::Xaml::Shapes::Shape^ Shape;          // Shape handle
    property Windows::UI::Xaml::Controls::TextBlock^ Back;     // Card back
  };
}
