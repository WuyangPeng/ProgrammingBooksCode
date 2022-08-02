//
// wargameSTL.cpp
// Learning how to convert a standard C++ code solution
// into a robust STL design
// Chris H. Pappas and William H. Murray, 2000
// 

#include <vector> // added for vector definitions
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef enum tagSuits {diamond, club, heart, spade} SUITS;

//**************************************************************
//STL pair data type containing int and SUITS
typedef struct pair<int,SUITS> ACARD_PAIR;

//**************************************************************
// class aSingleCard with defined methods
class aSingleCard {
  public:
    // non-STL int first;
    // non-STL SUITS suit;  
    // STL replacement
    ACARD_PAIR oneCard;
    aSingleCard() {oneCard.first = 0; oneCard.second = spade;};
    aSingleCard( SUITS s, int ir) {oneCard.second = s;
                                   oneCard.first = ir;};
    friend ostream& operator <<( ostream& out, aSingleCard& aCard );
};

//**************************************************************
// STL standard typedef for application-specific vectors
typedef vector<aSingleCard> CardVector;

//**************************************************************
// class WarDeck with defined methods
class WarDeck {
  public:
    WarDeck();
    void shuffleDeck();
    bool isDeckEmpty();
    aSingleCard drawCardFromDeck();

  protected:
    // non-STL #define DECK_SIZE      52
    #define CARDS_PER_SUIT 13
    CardVector fullDeck;
    int iCurrentCard;
};

WarDeck::WarDeck()
{
  iCurrentCard = 0;
  for( int i = 1; i <= CARDS_PER_SUIT; i++ ) {
    aSingleCard c1(diamond, i), c2(spade, i), c3(heart, i), c4(club, i);
    // non-STL fullDeck[iCurrentCard++] = c1;
    // non-STL fullDeck[iCurrentCard++] = c2;
    // non-STL fullDeck[iCurrentCard++] = c3;
    // non-STL fullDeck[iCurrentCard++] = c4;
    fullDeck.push_back( c1 );
    fullDeck.push_back( c2 );
    fullDeck.push_back( c3 );
    fullDeck.push_back( c4 );
  }
}

void WarDeck::shuffleDeck()
{
  typedef CardVector::iterator CardVectorIt;

  CardVectorIt Start, End;

  Start = fullDeck.begin();
  End   = fullDeck.end();

  random_shuffle( Start, End);
}

aSingleCard WarDeck::drawCardFromDeck()
{
/*  if( ! isDeckEmpty() )
    return fullDeck[--iCurrentCard];
  else {
    aSingleCard defaultCard( spade, 1 );
    return defaultCard;
  }
*/
  aSingleCard tempCard;
  if( !fullDeck.empty() ) {
    tempCard = fullDeck.front();
    fullDeck.erase(fullDeck.begin());
  }
  else {
    aSingleCard defaultCard( spade, 1 );
    tempCard = defaultCard;
  }
  return tempCard;
}

bool WarDeck::isDeckEmpty()
{
  // non-STL return iCurrentCard <= 0;
  return fullDeck.empty();
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
    // non-STL aSingleCard currentHand[CARDS_IN_HAND];
    CardVector currentHand;
    int currentScore;
    int cardBeingPlayed;
};

Opponent::Opponent( WarDeck & aDeck )
{
  currentScore = 0;
    for( int i = 0; i < CARDS_IN_HAND; i++ )
      // non-STL currentHand[i] = aDeck.drawCardFromDeck();
      currentHand.push_back(aDeck.drawCardFromDeck());
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
    
    if( card1.oneCard.first == card2.oneCard.first ) {
      opponent1.addUpPoints(1);
      opponent2.addUpPoints(1);
      cout << "Players tie\n" << endl;
      }
    else if( card1.oneCard.first > card2.oneCard.first ) {
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
  switch( aCard.oneCard.first ) {
    case  1: out << "Ace"  ; break;
    case 11: out << "Jack" ; break;
    case 12: out << "Queen"; break;
    case 13: out << "King" ; break;
    default:
      out << aCard.oneCard.first; break;
  }

  switch( aCard.oneCard.second ) {
    case diamond: out << " of Diamonds"; break;
    case spade  : out << " of Spades  "; break;
    case heart  : out << " of Hearts  "; break;
    case club   : out << " of Clubs   "; break;
  }

  return out;
};
