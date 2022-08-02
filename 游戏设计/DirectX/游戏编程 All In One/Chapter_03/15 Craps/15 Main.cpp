#include <iostream>
#include <stdlib.h>
#include <time.h>
 /* Function prototypes */
void ShowIntroScreen (void);
void ShowInformation (unsigned long Money);
short GetBet (void);
short DoDiceThrow (void);
unsigned short DoMoneyCalc (short Dice, short Bet, short BetMoney);
unsigned long GetAmount (void);
 /* Start game */
main (void)
{
 unsigned long MoneyEarned;
 unsigned long Money;

 short DiceValue;
 short Bet;
 short BetMoney;
  /* Show intro and setup game */
 ShowIntroScreen ();
 Money = 1000;

  /* Play while player has money  
     Keep 100 dollars for the cab home */
do
{
  ShowInformation (Money);
   // Get bet information */
  Bet         = GetBet ();
  BetMoney    = GetAmount ();
  DiceValue   = DoDiceThrow ();
  MoneyEarned = DoMoneyCalc (DiceValue, Bet, BetMoney);

  Money -= BetMoney;

   /* Show the number */
  if (MoneyEarned == 0)
  {
   std::cout << "You lost. Number was: " << DiceValue;
   std::cout << std::endl << std::endl;
  }
  else
  {
   std::cout << "You won " << MoneyEarned  - BetMoney;
   std::cout << " dollars. Number was: " << DiceValue;
   std::cout << std::endl << std::endl;

   Money += MoneyEarned;
  }
 } 
 while (Money > 100);
 std::cout << "Game Over. Keep $" << Money << " for the ride home";
 std::cout << std::endl;

 return 0;
}
 /* Show introduction screen */
void ShowIntroScreen (void)
{
 std::cout << "     Welcome to Craps 1.0";
 std::cout << std::endl << std::endl;
 std::cout << "Here are the rules:";
 std::cout << std::endl << std::endl;

 std::cout << "You have 1000 dollars to start gambling. ";
 std::cout << std::endl << std::endl;

 std::cout << "You can do three different bets. You can bet on ";
 std::cout << "numbers 2 and 12 which will give";
 std::cout << "you a win ratio of ";
 std::cout << "5 to 1 if you win. You can also bet on the numbers 4 ";
 std::cout << "and 10  ";
 std::cout << "which will give you a win ratio of 2.5 to 1. ";
 std::cout << std::endl;
 std::cout << "The last kind of bet you can do is on the numbers 6 ";
 std::cout << "and 8 which will give you a win ratio of 1.5 to 1.";
 std::cout << std::endl << std::endl;

 std::cout << "The minimum amount to bet is 10 dollars and the ";
 std::cout << "maximum 100 dollars.";
 std::cout << std::endl << std::endl;

 std::cout << "Have fun playing.";
 std::cout << std::endl << std::endl  << std::endl;
}
 /* Show money information */
void ShowInformation (unsigned long Money)
{
 std::cout << "You have : " << Money << " dollars.";
 std::cout << std::endl;
}
 /* Get player bet type */
short GetBet (void)
{
 unsigned short BetType;

  /* Get bet */
 std::cout << "Enter type of bet (1 = '6/8' 2 = '4/10' 3 = '2/12'): ";
 std::cin >> BetType;

  /* If bet invalid bet on 6/8 */
 if ((BetType == 1) || (BetType == 2) || (BetType == 3))
 {
  return BetType;
 }
 else
 {
  return 1;
 }
}
 /* Throw dice - randomize number */
short DoDiceThrow (void)
{
 short DiceValue;

  /* Get dice value */
 srand (time (NULL));
 DiceValue = (rand () % 11) + 2;

  /* If 4/10 get another number, this will make this 
     event more improbable so pay ratio is bigger */
 if ((DiceValue == 4) || (DiceValue == 10))
 {
  srand (time (NULL));
  DiceValue = (rand () % 12) + 1;
 }

  /* If 2/12 get another number, this will make this 
     event more improbable so pay ratio is bigger */
 if ((DiceValue == 2) || (DiceValue == 12))
 {
  srand (time (NULL));
  DiceValue = (rand () % 12) + 1;

  if ((DiceValue == 2) || (DiceValue == 12))
  {
   srand (time (NULL));
   DiceValue = (rand () % 12) + 1;
  }
 }

 return DiceValue;
}
 /* Calculate earnings */
unsigned short DoMoneyCalc (short Dice, short Bet, short BetMoney)
{
 unsigned long MoneyEarned = 0;
 
  /* See which type of bet the player made */
 switch (Bet)
 {
  /* 6/8 - pay amount of 1.5:1 */
 case 1:
  if ((Dice == 6) || (Dice == 8))
  {
   MoneyEarned = BetMoney * 1.5;
  }
  break;  break;
  /* 4/10 - pay amount of 2.5:1 */
 case 2:
  if ((Dice == 10) || (Dice == 4))
  {
   MoneyEarned = BetMoney * 2.5;
  }
  break;  break;
  /* 2/12 - pay amount of 5:1 */
 case 3:
  if ((Dice == 2) || (Dice == 12))
  {
   MoneyEarned = BetMoney * 5;
  }
  break;
 default:
  MoneyEarned = 0;
  break;
 }
 
 return MoneyEarned;
}
 /* Get ammount to bet */
unsigned long GetAmount (void)
{
 unsigned short BetAmount;
  
  /* Get bet amount */
 std::cout << "Enter amount to bet (min 10 - max 100): ";
 std::cin >> BetAmount;

  /* If bet out of range fix it */
 if (BetAmount < 10)
 {
  BetAmount = 10;
 }

 if (BetAmount > 100)
 {
  BetAmount = 100;
 }

 return BetAmount;
}
