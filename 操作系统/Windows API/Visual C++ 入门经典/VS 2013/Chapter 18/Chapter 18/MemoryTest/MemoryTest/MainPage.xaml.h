//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "Card.h"

namespace MemoryTest
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
  private:
    void Shape_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
    void Cardback_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
    void Card_Entered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
    void Card_Exited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);

  private:
    // Data members
    size_t cardCount;                                                        // The number of cards
    Platform::Array<Windows::UI::Xaml::Controls::Grid^>^ grids;
    Platform::Array<Windows::UI::Xaml::Shapes::Ellipse^>^ circles;
    Platform::Array<Windows::UI::Xaml::Shapes::Rectangle^>^ squares;
    Platform::Array<Windows::UI::Xaml::Shapes::Polygon^>^ triangles;
    Platform::Array<Windows::UI::Xaml::Controls::TextBlock^>^ cardBacks;
    Platform::Array<Card^>^ cardPack;                                        // The pack of cards

    Windows::UI::Xaml::Media::SolidColorBrush^ steelBrush;                   // Card highlighted
    Windows::UI::Xaml::Media::SolidColorBrush^ azureBrush;                   // Card normal

    // Game records
    Card^  card1Up;                                                          // 1st card turned up
    Card^  card2Up;                                                          // 2nd card turned up
    size_t pairCount;                                                        // Number of pairs found
    Platform::Collections::Vector<Card^>^ pairsFound;                        // Cards in pairs found

    // Type names for card elements
    Platform::String^ typeCircle;
    Platform::String^ typeSquare;
    Platform::String^ typeTriangle;

  private:
    // Game functions
    void InitializeCardPack();                                               // Initialize cardPack to two of each card
    void SetUpUIState();                                                     // Initialize the child elements of cardGrid
    void InitializeGame();                                                   // Set up a game with a shuffled cardPack
    inline void ShuffleCards();                                              // Shuffle the cards
    void GameOver();                                                         // End the game
    void DisableCard(Card^ card);
    bool IsFound(Windows::UI::Xaml::Controls::TextBlock^ back);              // Test for back of card in existing pair
    void MainPage::HideMessages();                                           // Hide all messages in the message area
    void Show_How_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
    void Start_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
    void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
  };
}
