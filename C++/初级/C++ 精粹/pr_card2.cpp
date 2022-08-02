/*********************************************************************

  Filename:  pr_card2.cpp
  Section:   16.3   User-Defined Types: Output
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

// Modified pr_card to use overloaded << for print functions

#include <iostream.h>
#include <stdlib.h>                //for random number
#include <time.h>                  //for random number seed


char  pips_symbol[14] = { '?', 'A', '2', '3', '4', '5',
                '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
char  suit_symbol[4] = { 'c', 'd', 'h', 's' };

enum suit { clubs, diamonds, hearts, spades };

class pips {
public:
   void  assign(int n) { p = n % 13 + 1; }
   friend ostream& operator<<(ostream& out, pips x);
private:
   int  p;
};

class card {
public:
   suit  s;
   pips  p;
   void  assign(int n)
      { cd = n; s = suit(n / 13); p.assign(n); }
   friend ostream& operator<<(ostream& out, card cd);
private:
   int  cd;                 //a cd is from 0 to 51
};

class deck {
public:
   void  init_deck();
   void  shuffle();
   void  deal(int, int, card*);
   friend ostream& operator<<(ostream& out, deck x);
private:
   card d[52];
};


ostream& operator<<(ostream& out, pips x)
{
    return (out << pips_symbol[x.p]);
}

ostream& operator<<(ostream& out, card cd)
{
    return (out << cd.p << suit_symbol[cd.s] << "  " );
}

ostream& operator<<(ostream& out, deck x)
{
   for (int i = 0; i < 52; ++i) {
      if (i % 13 == 0)      //13 cards to a line
         out << endl;
      out << x.d[i];
   }
   return out;
}

void  deck::init_deck()
{
   for(int i = 0; i < 52; ++i)
      d[i].assign(i);
}

void  deck::shuffle()
{
   for (int i = 0; i < 52; ++i) {
      int k = rand() % 52;
      card t = d[i]; d[i] = d[k]; d[k] = t; //swap two cards
   }
}

void deck::deal(int n, int pos, card *hand)
{
   for(int i = pos; i < pos +n; ++i)
      hand[i - pos] = d[i];
}

int main()
{
   card one_hand[9];
   deck dk;
   int  i, j, k, fcnt = 0, sval[4];
   int  ndeal, nc, nhand;

   do {
      cout << "\nEnter no. of cards in each hand (5-9): ";
      cin  >> nc;
   } while (nc < 5 || nc > 9);

   nhand = 52 / nc;
   cout << "\nEnter no. of hands to deal: ";
   cin  >> ndeal;
   randomize();
   dk.init_deck();
   cout << dk;      // print using overloaded <<

   for (k = 0; k < ndeal; k += nhand) {
     if ((nhand + k) > ndeal)
        nhand = ndeal - k;
     dk.shuffle();
     for(i = 0; i < nc * nhand; i += nc) {
        for (j = 0; j < 4; ++j)
           sval[j] = 0;
        dk.deal(nc, i, one_hand);
        for (j = 0; j < nc; ++j)
           sval[one_hand[j].s] ++ ;
        for (j = 0; j < 4; ++j)
          if (sval[j] >= 5)
             fcnt++;
     }
   }
   cout << "\n\nIn " << ndeal << " ";
   cout << nc << "-card hands there were ";
   cout << fcnt << " flushes\n  ";
}
