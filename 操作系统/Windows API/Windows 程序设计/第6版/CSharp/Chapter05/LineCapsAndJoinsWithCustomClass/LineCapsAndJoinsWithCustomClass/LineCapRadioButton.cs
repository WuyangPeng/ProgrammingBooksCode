using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace LineCapsAndJoinsWithCustomClass
{
    public class LineCapRadioButton : RadioButton
    {
        public PenLineCap LineCapTag { set; get; }
    }
}
