//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <algorithm>
#include <random>

using namespace MemoryTest;

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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage() :card1Up{}, card2Up{}, pairCount{}
{
  InitializeComponent();
  // Brushes for card colors
  steelBrush = ref new SolidColorBrush(Windows::UI::Colors::SteelBlue);
  azureBrush = ref new SolidColorBrush(Windows::UI::Colors::Azure);

  // cardCount is number of rows x number of columns in cardGrid
  cardCount = cardGrid->ColumnDefinitions->Size*cardGrid->RowDefinitions->Size;
  pairsFound = ref new Platform::Collections::Vector<Card^>(cardCount);

  // Initialize type names for card elements
  typeCircle = Ellipse::typeid->FullName;
  typeSquare = Rectangle::typeid->FullName;
  typeTriangle = Polygon::typeid->FullName;

  // Create arrays to store element handles for the cards
  // Each type is in a separate array and will be stored in card sequence
  circles = ref new Array<Ellipse^>(cardCount);
  triangles = ref new Array<Polygon^>(cardCount);
  squares = ref new Array<Rectangle^>(cardCount);
  cardBacks = ref new Array<TextBlock^>(cardCount);
  grids = ref new Array<Grid^>(cardCount);
  InitializeCardPack();
  SetUpUIState();
  InitializeGame();
}


void MemoryTest::MainPage::Shape_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
  // With this event there is always at least one card up but could be two.
  // If only one card is up, the handle is in card1Up
  Shape^ shape = safe_cast<Shape^>(sender);
  if (card1Up && card2Up)
  {  // Two cards up so turn over both cards
    card1Up->Shape->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    card1Up->Back->Visibility = Windows::UI::Xaml::Visibility::Visible;
    card2Up->Shape->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    card2Up->Back->Visibility = Windows::UI::Xaml::Visibility::Visible;

    // Enable events for all card backs and background grids
    for (size_t i{}; i < cardBacks->Length; ++i)
    {
      if (IsFound(cardBacks[i]))
        continue;
      cardBacks[i]->IsTapEnabled = true;
      grids[i]->IsHitTestVisible = true;
    }
    card1Up = card2Up = nullptr;  // Reset both handles to cards up
  }
  else
  {  // only one card up and it was clicked so turn over the card
    card1Up->Shape->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    card1Up->Back->Visibility = Windows::UI::Xaml::Visibility::Visible;
    card1Up = nullptr;
  }
}


void MemoryTest::MainPage::Cardback_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{ // There may be 0 or 1 cards already turned over
  // If there is 1, the card handle will be in card1Up
  TextBlock^ cardBack = safe_cast<TextBlock^>(sender);                             // Always a card back handle
  cardBack->Visibility = Windows::UI::Xaml::Visibility::Collapsed;                 // Hide the back

  // Find the card for the back so the shape can be made visible
  Card^ theCard;
  for (auto card : cardPack)
  {
    if (cardBack == card->Back)
    { // We have found the card so show the front
      card->Shape->Visibility = Windows::UI::Xaml::Visibility::Visible;
      theCard = card;
      break;
    }
  }
  if (!card1Up)
  {
    card1Up = theCard;
  }
  else
  {
    card2Up = theCard;
    if (card1Up->Type == card2Up->Type && card1Up->Color == card2Up->Color)
    { // We have a pair!
      pairsFound->Append(card1Up);
      pairsFound->Append(card2Up);
      DisableCard(card1Up);
      DisableCard(card2Up);
      card1Up = card2Up = nullptr;
      if (++pairCount == cardCount / 2)
        GameOver();
    }
    else
    { // Two cards up but no pair so we now want a Tapped event on either
      // Disable Tapped event for card backs and PointerEntered 
      // and PointerExited events for other cards
      for (size_t i{}; i < cardBacks->Length; ++i)
      {
        if (cardBacks[i] == card1Up->Back || cardBacks[i] == card2Up->Back)
          continue;
        cardBacks[i]->IsTapEnabled = false;
        grids[i]->IsHitTestVisible = false;
      }
    }
  }
}

void MemoryTest::MainPage::Card_Entered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
  safe_cast<Grid^>(sender)->Background = steelBrush;
}


void MemoryTest::MainPage::Card_Exited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
  safe_cast<Grid^>(sender)->Background = azureBrush;
}

// Initialize the pack of cards so it contains 12 different pairs
void MainPage::InitializeCardPack()
{
  // Create arrays of the shape types and colors
  Array<String^>^ shapeTypes  { typeCircle, typeSquare, typeTriangle };
  Array<SolidColorBrush^>^ colors {
    ref new SolidColorBrush(Windows::UI::Colors::Red),
    ref new SolidColorBrush(Windows::UI::Colors::Green),
    ref new SolidColorBrush(Windows::UI::Colors::Blue),
    ref new SolidColorBrush(Windows::UI::Colors::Yellow)
  };
  // Initialize the card pack
  cardPack = ref new Array<Card^>(cardCount);
  size_t packIndex {};                                       // Index to cardPack array
  Card^ card;
  for (auto color : colors)
  {
    for (auto shapeType : shapeTypes)
    {
      card = ref new Card();                                 // Create a card...
      card->Type = shapeType;                                // with the current type...
      card->Color = color;                                   // ... and color
      card->Shape = nullptr;                                 // we will find the shape...
      card->Back = nullptr;                                  // ...and back later.
      cardPack[packIndex++] = card;                          // Store the card and ...
      cardPack[packIndex++] = ref new Card(card);            // ...a copy in the pack.
    }
  }
}

// Set up the initial UI state and stores elements in grid cell order 
void MainPage::SetUpUIState()
{
  // Handle to the collection of grids in cardGrid
  auto elements = cardGrid->Children;

  size_t index{};                                            // Index to shape arrays
  const size_t rowLength(cardGrid->ColumnDefinitions->Size); // Length of a grid row

  // Iterate over the child elements to cardGrid and store 
  // the Grid^ handles in the grids array in sequence
  for (UIElement^ element : elements)
  {
    String^ elementType = element->GetType()->FullName;       // Get element type
    if (Grid::typeid->FullName == elementType)                // Make sure it's a Grid
    {
      auto grid = safe_cast<Grid^>(element);
      auto row = cardGrid->GetRow(grid);                     // Get the grid row 
      auto column = cardGrid->GetColumn(grid);               // and column location. 
      index = row*rowLength + column;                        // Index for row/column
      grids[index] = grid;                                   // Save the grid
      // A grid in each cell contains another grid as child.
      // We know that's always the case so get the child-grid:
      grid = safe_cast<Grid^>(grid->Children->GetAt(0));
      auto shapes = grid->Children;                          // Get the child shapes

      // Iterate over the child elements to the current Grid and store
      // the shape element handles in the array for their type in sequence
      for (UIElement^ element : shapes)
      {
        elementType = element->GetType()->FullName;          // Get element type
        // Store a circle in circles array & do the same for the other elements
        // Only card backs will be visible - all other shapes collapsed.
        if (typeCircle == elementType)
        {
          circles[index] = safe_cast<Ellipse^>(element);
          element->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        }
        else if (typeSquare == elementType)
        {
          squares[index] = safe_cast<Rectangle^>(element);
          element->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        }
        else if (typeTriangle == elementType)
        {
          triangles[index] = safe_cast<Polygon^>(element);
          element->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        }
        else if (TextBlock::typeid->FullName == elementType)
        {
          cardBacks[index] = safe_cast<TextBlock^>(element);
          element->Visibility = Windows::UI::Xaml::Visibility::Visible;
        }
      }

    }
  }
}

// Shuffle the cards and deal
void MainPage::InitializeGame()
{
  card1Up = card2Up = nullptr;                               // No cards up
  pairCount = 0;                                             // No pairs found
  pairsFound->Clear();                                       // Clear pairs record

  // Null the handles to UI elements
  for (auto card : cardPack)
  {
    card->Shape = nullptr;
    card->Back = nullptr;
  }
  ShuffleCards();                                            // Shuffle cardPack

  // Set the shapes in the Grid elements to represent the cards dealt
  for (size_t i{}; i < cardCount; ++i)
  {
    cardPack[i]->Back = cardBacks[i];
    if (cardPack[i]->Type == typeCircle)
    {
      circles[i]->Fill = cardPack[i]->Color;
      cardPack[i]->Shape = circles[i];
    }
    else if (cardPack[i]->Type == typeSquare)
    {
      squares[i]->Fill = cardPack[i]->Color;
      cardPack[i]->Shape = squares[i];
    }
    else if (cardPack[i]->Type == typeTriangle)
    {
      triangles[i]->Fill = cardPack[i]->Color;
      cardPack[i]->Shape = triangles[i];
    }
    cardPack[i]->Shape->IsTapEnabled = true;

    // Set up UI to show card backs & enable events
    cardBacks[i]->Visibility = Windows::UI::Xaml::Visibility::Visible;
    cardBacks[i]->IsTapEnabled = true;
    // Ensure background grids are hit test visible & opaque
    grids[i]->IsHitTestVisible = true;
    grids[i]->Opacity = 1;
    // Ensure all shapes are invisible & opaque
    circles[i]->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    squares[i]->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    triangles[i]->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    circles[i]->Opacity = 1;
    squares[i]->Opacity = 1;
    triangles[i]->Opacity = 1;
  }
}

// Shuffle the cards
void MainPage::ShuffleCards()
{
  std::random_device gen;                // Random number source
  std::random_shuffle(begin(cardPack), end(cardPack), [&gen](size_t n) {
    std::uniform_int_distribution<int> distribution(1, n);
    return distribution(gen)-1;  });
}

// End current game
void MainPage::GameOver()
{
  HideMessages();                                            // Hide any other messages
  winMessage->Opacity = 1.0;                                 // Show the win message
}

// Hide messages in the message area
void MainPage::HideMessages()
{
  auto messageCollection = messageArea->Children;
  for (UIElement^ element : messageCollection)
  {
    element->Opacity = 0;
  }
}

// Disable a card
void MainPage::DisableCard(Card^ card)
{
  card->Shape->IsTapEnabled = false;                         // Disable Tapped event...
  card->Shape->Opacity = 0.5;

  // Get the parent Grid for shape
  auto grid = safe_cast<Grid^>(card->Shape->Parent);
  grid = safe_cast<Grid^>(grid->Parent);
  grid->IsHitTestVisible = false;                            // Disable hit test
  grid->Background = azureBrush;                             // Make sure of color
}

// Test for back of card in existing pair
bool MainPage::IsFound(TextBlock^ back)
{
  for (auto cardFound : pairsFound)
  {
    if (cardFound  && cardFound->Back == back) return true;
  }
  return false;
}


void MemoryTest::MainPage::Show_How_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
  HideMessages();                                            // Clear the message area
  playButtonTurn->Begin();                                   // Start the animation
  playMessage->Opacity = 1;                                  // Show the instructions
}


void MemoryTest::MainPage::Start_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
  HideMessages();                                            // Clear the message area
  InitializeGame();                                          // Reset the game
}


void MemoryTest::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
  // Scale all card shapes so they squarely fit their grid cells.
  // Iterate over all children of the cardGrid grid.
  for (size_t i{}; i < cardGrid->Children->Size; ++i)
  {
    // Get the small grid in each cell.
    Grid^ grid = safe_cast<Grid^>(cardGrid->Children->GetAt(i));

    // Get the small grid inside the small grid.
    Grid^ childGrid = safe_cast<Grid^>(grid->Children->GetAt(0));

    // Calculate the scaling factor to keep everything square.
    double scale = 1.0;
    if (grid->ActualWidth >= grid->ActualHeight)
    { // Landscape mode
      scale = 0.8*grid->ActualHeight / childGrid->ActualHeight;
    }
    else
    { // Portrait mode
      scale = 0.8*grid->ActualWidth / childGrid->ActualWidth;
    }

    // Apply scaling factor.
    auto scaleTransform = ref new ScaleTransform();
    scaleTransform->ScaleX = scale;
    scaleTransform->ScaleY = scale;
    childGrid->RenderTransformOrigin = Point(0.5, 0.5);      // Center of object
    childGrid->RenderTransform = scaleTransform;
  }
}
