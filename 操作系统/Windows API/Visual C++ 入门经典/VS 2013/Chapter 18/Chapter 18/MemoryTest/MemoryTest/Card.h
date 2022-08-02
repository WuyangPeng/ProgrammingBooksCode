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
      type = card->type;
      color = card->color;
      shape = card->shape;
      back = card->back;
    }

  public:
    property Platform::String^ type;                           // Shape type
    property Windows::UI::Xaml::Media::SolidColorBrush^ color; // Color
    property Windows::UI::Xaml::Shapes::Shape^ shape;          // Shape handle
    property Windows::UI::Xaml::Controls::TextBlock^ back;     // Card back
  };
}
