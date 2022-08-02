using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Ch12CardLib;

namespace Ch12CardClient
{
   class Program
   {
      static void Main(string[] args)
      {
         #region Code for "Adding a Cards Collection to CardLib" section.
         //Deck myDeck = new Deck();
         //myDeck.Shuffle();
         //for (int i = 0; i < 52; i++)
         //{
         //   Card tempCard = myDeck.GetCard(i);
         //   Console.Write(tempCard.ToString());
         //   if (i != 51)
         //      Console.Write(", ");
         //   else
         //      Console.WriteLine();
         //}
         //Console.ReadKey();
         #endregion

         #region Code for "Adding Deep Copying to CardLib" section.
         //Deck deck1 = new Deck();
         //Deck deck2 = (Deck)deck1.Clone();
         //Console.WriteLine("The first card in the original deck is: {0}",
         //                  deck1.GetCard(0));
         //Console.WriteLine("The first card in the cloned deck is: {0}",
         //                  deck2.GetCard(0));
         //deck1.Shuffle();
         //Console.WriteLine("Original deck shuffled.");
         //Console.WriteLine("The first card in the original deck is: {0}",
         //                  deck1.GetCard(0));
         //Console.WriteLine("The first card in the cloned deck is: {0}",
         //                  deck2.GetCard(0));
         //Console.ReadKey();
         #endregion

         #region Code for "Adding Operator Overloads to CardLib" section.
         Card.isAceHigh = true;
         Console.WriteLine("Aces are high.");
         Card.useTrumps = true;
         Card.trump = Suit.Club;
         Console.WriteLine("Clubs are trumps.");

         Card card1, card2, card3, card4, card5;
         card1 = new Card(Suit.Club, Rank.Five);
         card2 = new Card(Suit.Club, Rank.Five);
         card3 = new Card(Suit.Club, Rank.Ace);
         card4 = new Card(Suit.Heart, Rank.Ten);
         card5 = new Card(Suit.Diamond, Rank.Ace);
         Console.WriteLine("{0} == {1} ? {2}",
              card1.ToString(), card2.ToString(), card1 == card2);
         Console.WriteLine("{0} != {1} ? {2}",
              card1.ToString(), card3.ToString(), card1 != card3);
         Console.WriteLine("{0}.Equals({1}) ? {2}",
              card1.ToString(), card4.ToString(), card1.Equals(card4));
         Console.WriteLine("Card.Equals({0}, {1}) ? {2}",
              card3.ToString(), card4.ToString(), Card.Equals(card3, card4));
         Console.WriteLine("{0} > {1} ? {2}",
              card1.ToString(), card2.ToString(), card1 > card2);
         Console.WriteLine("{0} <= {1} ? {2}",
              card1.ToString(), card3.ToString(), card1 <= card3);
         Console.WriteLine("{0} > {1} ? {2}",
              card1.ToString(), card4.ToString(), card1 > card4);
         Console.WriteLine("{0} > {1} ? {2}",
              card4.ToString(), card1.ToString(), card4 > card1);
         Console.WriteLine("{0} > {1} ? {2}",
              card5.ToString(), card4.ToString(), card5 > card4);
         Console.WriteLine("{0} > {1} ? {2}",
              card4.ToString(), card5.ToString(), card4 > card5);
         Console.ReadKey();
         #endregion
      }
   }
}
