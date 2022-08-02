//
// wargame.cpp
// Learning how to convert a standard C++ code solution
// into a robust STL design
// Chris H. Pappas and William H. Murray, 2000
// 

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef enum tagSuits {diamond, club, heart, spade} SUITS;

//**************************************************************
// class aSingleCard with defined methods
class aSingleCard {
  public:
    int iRank;
    SUITS suit;  
    aSingleCard() {iRank = 0; suit = spade;};
    aSingleCard( SUITS s, int ir) {suit = s; iRank = ir;};
    friend ostream& operator <<( ostream& out, aSingleCard& aCard );
};

//**************************************************************
// class WarDeck with defined methods
class WarDeck {
  public:
    WarDeck();
    void shuffleDeck();
    bool isDeckEmpty();
    aSingleCard drawCardFromDeck();

  protected:
    #define DECK_SIZE      52
    #define CARDS_PER_SUIT 13
    aSingleCard fullDeck[DECK_SIZE];
    int iCurrentCard;
};

WarDeck::WarDeck()
{
  iCurrentCard = 0;
  for( int i = 1; i <= CARDS_PER_SUIT; i++ ) {
    aSingleCard c1(diamond, i), c2(spade, i), c3(heart, i), c4(club, i);
    fullDeck[iCurrentCard++] = c1;
    fullDeck[iCurrentCard++] = c2;
    fullDeck[iCurrentCard++] = c3;
    fullDeck[iCurrentCard++] = c4;
  }
}

void WarDeck::shuffleDeck()
{
  random_shuffle( fullDeck, fullDeck+52);
}

aSingleCard WarDeck::drawCardFromDeck()
{
  if( ! isDeckEmpty() )
    return fullDeck[--iCurrentCard];
  else {
    aSingleCard defaultCard( spade, 1 );
    return defaultCard;
  }
}

bool WarDeck::isDeckEmpty()
{
  return iCurrentCard <= 0;
}

//**************************************************************
// class Opponent with defined methods
class Opponent {
  public:
    Opponent( WarDeck& );
    aSingleCard drawCardFromDeck();
    void addUpPoints( int );
    int what_sTheScore();
    void putBackCard( WarDeck&);

  protected:
    #define CARDS_IN_HAND 3
    aSingleCard currentHand[CARDS_IN_HAND];
    int currentScore;
    int cardBeingPlayed;
};

Opponent::Opponent( WarDeck & aDeck )
{
  currentScore = 0;
    for( int i = 0; i < CARDS_IN_HAND; i++ )
      currentHand[i] = aDeck.drawCardFromDeck();
    cardBeingPlayed = 0;
}

aSingleCard Opponent::drawCardFromDeck()
{

  cardBeingPlayed = rand() % 3;
  return currentHand[cardBeingPlayed];
}

void Opponent::addUpPoints( int howMany )
{
  currentScore += howMany;
}

int Opponent::what_sTheScore()
{
  return currentScore;
}

void Opponent::putBackCard(WarDeck& aDeck)
{
  currentHand[cardBeingPlayed] = aDeck.drawCardFromDeck();
}

//**************************************************************
// main() function
void main( void )
{
  WarDeck actualDeck;
  actualDeck.shuffleDeck();

  srand( (unsigned int)time( NULL ) );

  Opponent opponent1(actualDeck);
  Opponent opponent2(actualDeck);

  while( !actualDeck.isDeckEmpty() ) {
    aSingleCard card1 = opponent1.drawCardFromDeck();
    cout << "Opponent 1 plays " << card1 << endl;
    aSingleCard card2 = opponent2.drawCardFromDeck();
    cout << "Opponent 2 plays " << card2 << endl;
    
    if( card1.iRank == card2.iRank ) {
      opponent1.addUpPoints(1);
      opponent2.addUpPoints(1);
      cout << "Players tie\n" << endl;
      }
    else if( card1.iRank > card2.iRank ) {
      opponent1.addUpPoints(2);
      cout << "Opponent 1 wins round\n";
      }
    else {
      opponent2.addUpPoints(2);
      cout << "Opponent 2 wins round\n";
      }

    opponent1.putBackCard(actualDeck);
    opponent2.putBackCard(actualDeck);

    cout << "\n\nPress ENTER to continue."   << endl;
    cin.get();

  }

  cout << "Opponent 1 what_sTheScore " << opponent1.what_sTheScore() << endl;
  cout << "Opponent 2 what_sTheScore " << opponent2.what_sTheScore() << endl;
      
}

//**************************************************************
// class aSingleCard friend overloaded insertion operator
ostream& operator <<( ostream& out, aSingleCard& aCard )
{
  switch( aCard.iRank ) {
    case  1: out << "Ace"  ; break;
    case 11: out << "Jack" ; break;
    case 12: out << "Queen"; break;
    case 13: out << "King" ; break;
    default:
      out << aCard.iRank; break;
  }

  switch( aCard.suit ) {
    case diamond: out << " of Diamonds"; break;
    case spade  : out << " of Spades  "; break;
    case heart  : out << " of Hearts  "; break;
    case club   : out << " of Clubs   "; break;
  }

  return out;
};
