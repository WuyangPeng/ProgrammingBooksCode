using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Ch13CardLib;

namespace Ch13CardClient
{
   public class Player
   {
      public string Name { get; private set; }

      public Cards PlayHand { get; private set; }

      private Player()
      {
      }

      public Player(string newName)
      {
         Name = newName;
         PlayHand = new Cards();
      }

      public bool HasWon()
      {
         bool won = true;
         Suit match = PlayHand[0].suit;
         for (int i = 1; i < PlayHand.Count; i++)
         {
            won &= PlayHand[i].suit == match;
         }
         return won;
      }
   }
}
