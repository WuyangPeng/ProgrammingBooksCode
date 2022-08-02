using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Ch25Ex05
{
   /// <summary>
   /// Interaction logic for Card.xaml
   /// </summary>
   public partial class Card : UserControl
   {
      public static string[] Suits = { "Club", "Diamond", "Heart", "Spade" };

      public static DependencyProperty SuitProperty = DependencyProperty.Register(
         "Suit",
         typeof(string),
         typeof(Card),
         new PropertyMetadata("Club", new PropertyChangedCallback(OnSuitChanged)),
         new ValidateValueCallback(ValidateSuit));

      public static DependencyProperty RankProperty = DependencyProperty.Register(
         "Rank",
         typeof(int),
         typeof(Card),
         new PropertyMetadata(1),
         new ValidateValueCallback(ValidateRank));

      public Card()
      {
         InitializeComponent();
      }

      public string Suit
      {
         get { return (string)GetValue(SuitProperty); }
         set { SetValue(SuitProperty, value); }
      }

      public int Rank
      {
         get { return (int)GetValue(RankProperty); }
         set { SetValue(RankProperty, value); }
      }

      public static bool ValidateSuit(object suitValue)
      {
         string suitValueString = (string)suitValue;
         if (suitValueString != "Club" && suitValueString != "Diamond"
            && suitValueString != "Heart" && suitValueString != "Spade")
         {
            return false;
         }
         return true;
      }

      public static bool ValidateRank(object rankValue)
      {
         int rankValueInt = (int)rankValue;
         if (rankValueInt < 1 || rankValueInt > 12)
         {
            return false;
         }
         return true;
      }

      private void SetTextColor()
      {
         if (Suit == "Club" || Suit == "Spade")
         {
            RankLabel.Foreground = new SolidColorBrush(Color.FromRgb(0, 0, 0));
            SuitLabel.Foreground = new SolidColorBrush(Color.FromRgb(0, 0, 0));
            RankLabelInverted.Foreground = new SolidColorBrush(Color.FromRgb(0, 0, 0));
         }
         else
         {
            RankLabel.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
            SuitLabel.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
            RankLabelInverted.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
         }
      }

      public static void OnSuitChanged(DependencyObject source,
         DependencyPropertyChangedEventArgs args)
      {
         ((Card)source).SetTextColor();
      }
   }
}