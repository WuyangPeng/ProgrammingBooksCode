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
   /// Interaction logic for MainWindow.xaml
   /// </summary>
   public partial class MainWindow : Window
   {
      private Card currentCard;
      private Point offset;
      private Random random = new Random();

      public MainWindow()
      {
         InitializeComponent();
      }

      private void Grid_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
      {
         if (e.Source is Card)
         {
            currentCard = (Card)e.Source;
            offset = Mouse.GetPosition(currentCard);
            contentGrid.Children.Remove(currentCard);
         }
         else
         {
            currentCard = new Card
            {
               Suit = Card.Suits[random.Next(0, 4)],
               Rank = random.Next(1, 13)
            };
            currentCard.HorizontalAlignment = HorizontalAlignment.Left;
            currentCard.VerticalAlignment = VerticalAlignment.Top;
            offset = new Point(50, 75);
         }
         contentGrid.Children.Add(currentCard);
         PositionCard();
      }

      private void Grid_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
      {
         currentCard = null;
      }

      private void Grid_MouseMove(object sender, MouseEventArgs e)
      {
         if (currentCard != null)
         {
            PositionCard();
         }
      }

      private void PositionCard()
      {
         Point mousePos = Mouse.GetPosition(this);
         currentCard.Margin =
            new Thickness(mousePos.X - offset.X, mousePos.Y - offset.Y, 0, 0);
      }
   }
}
