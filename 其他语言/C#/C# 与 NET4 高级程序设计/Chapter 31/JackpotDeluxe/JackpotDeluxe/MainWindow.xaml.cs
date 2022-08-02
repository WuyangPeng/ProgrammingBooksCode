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
using System.Windows.Shapes;

namespace JackpotDeluxe
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		private int totalPoints = 0;
		private int totalAttempts = 0;
		private int MaxAttempts = 20;
		
		public MainWindow()
		{
			this.InitializeComponent();

			// Insert code required on object creation below this point.
		}

		private void btnSpin_MouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
		{
			// Add 1 to number of tries. 
			this.txtAttempts.Text = string.Format("Attempts: {0}", (++totalAttempts).ToString());
			
			// Last attempt??
			if (totalAttempts >= MaxAttempts)
			{
				DoLosingCondition();
			}
			
			// Spin each control.
			int randomOne = this.imgFirst.Spin();
			int randomTwo = this.imgSecond.Spin();
			int randomThree = this.imgThird.Spin();
			
			// Caluculate the new score. To make things simple, players only get 
			// points if all three images are identical. 
			if (randomOne == randomTwo && randomTwo == randomThree)
			{
				// Adjust points. 
				totalPoints += 10;
				this.txtScore.Text = string.Format("Score: {0}", totalPoints.ToString());
		
				// Did we get 100 or more points?
				if (totalPoints >= 100)
				{
					DoWinningCondition();
				}
			}
		}
		
		private void DoLosingCondition()
		{
			// Change text.
			this.txtInstructions.Text = "YOU LOSE!";
			this.txtInstructions.FontSize = 80;
			this.txtInstructions.Foreground = new SolidColorBrush(Colors.Gray);
		
			// Disable button, game over dude!
			this.btnSpin.IsEnabled = false;
		}
	
		private void DoWinningCondition()
		{
			// Change text.
			this.txtInstructions.Text = "YOU WIN!";
			this.txtInstructions.FontSize = 80;
			this.txtInstructions.Foreground = new SolidColorBrush(Colors.Orange);
		
			// Disable button, game over dude!
			this.btnSpin.IsEnabled = false;
		}
	}
}