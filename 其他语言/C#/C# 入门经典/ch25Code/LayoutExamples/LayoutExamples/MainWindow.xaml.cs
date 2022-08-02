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

namespace LayoutExamples
{
   /// <summary>
   /// Interaction logic for MainWindow.xaml
   /// </summary>
   public partial class MainWindow : Window
   {
      public MainWindow()
      {
         InitializeComponent();
      }

      private void canvasWindowButton_Click(object sender, RoutedEventArgs e)
      {
         CanvasWindow window = new CanvasWindow();
         window.ShowDialog();
      }

      private void dockPanelWindowButton_Click(object sender, RoutedEventArgs e)
      {
         DockPanelWindow window = new DockPanelWindow();
         window.ShowDialog();
      }

      private void gridWindowButton_Click(object sender, RoutedEventArgs e)
      {
         GridWindow window = new GridWindow();
         window.ShowDialog();
      }

      private void stackPanelWindowButton_Click(object sender, RoutedEventArgs e)
      {
         StackPanelWindow window = new StackPanelWindow();
         window.ShowDialog();
      }

      private void wrapPanelWindowButton_Click(object sender, RoutedEventArgs e)
      {
         WrapPanelWindow window = new WrapPanelWindow();
         window.ShowDialog();
      }
   }
}
