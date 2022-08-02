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
using System.Windows.Media.Animation;

namespace MyCustomControl
{
	/// <summary>
	/// Interaction logic for SpinControl.xaml
	/// </summary>
	public partial class SpinControl
	{
		// An array of BitmapImage objects.
		private BitmapImage[] images = new BitmapImage[3];
			
		public SpinControl()
		{
			this.InitializeComponent();
		}
		
		private void SpinControl_Loaded(object sender, System.Windows.RoutedEventArgs e)
		{
			// Fill the ImageSource array with each image.
			images[0] = new BitmapImage(new Uri("Cherries.png", UriKind.Relative));
			images[1] = new BitmapImage(new Uri("Jackpot.jpg", UriKind.Relative));
			images[2] = new BitmapImage(new Uri("Limes.jpg", UriKind.Relative));
		}
		
		public int Spin()
		{
			// Randomly put of the images into the Image control.
			Random r = new Random(DateTime.Now.Millisecond);
			int randomNumber = r.Next(3);
			this.imgDisplay.Source = images[randomNumber];
			
			// Start our storyboard animation!
			((Storyboard)Resources["SpinImageStoryboard"]).Begin();
			return randomNumber;	
		}
	}
}
