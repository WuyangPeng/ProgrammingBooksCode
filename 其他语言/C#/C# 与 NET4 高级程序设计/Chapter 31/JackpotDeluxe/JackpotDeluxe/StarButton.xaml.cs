using System;
using System.Collections.Generic;
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

namespace JackpotDeluxe
{
	/// <summary>
	/// Interaction logic for StarButton.xaml
	/// </summary>
	public partial class StarButton : UserControl
	{
		public StarButton()
		{
			this.InitializeComponent();
		}

		private void StarControl_MouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
		{
			// Parameter 1 : Which control we are working with.
			// Parameter 2 : Which state to transition to.
			// Parameter 3 : Do we want to use transition times? 
			VisualStateManager.GoToState(this, "MouseDownStar", true);
		}

		private void StarControl_MouseEnter(object sender, System.Windows.Input.MouseEventArgs e)
		{
			VisualStateManager.GoToState(this, "MouseEnterStar", true);
		}

		private void StarControl_MouseLeave(object sender, System.Windows.Input.MouseEventArgs e)
		{
			VisualStateManager.GoToState(this, "MouseExitStar", true);
		}
	}
}