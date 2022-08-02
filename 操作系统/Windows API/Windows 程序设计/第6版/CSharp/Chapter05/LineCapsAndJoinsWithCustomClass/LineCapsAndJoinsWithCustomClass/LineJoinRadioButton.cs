using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace LineCapsAndJoinsWithCustomClass
{
    public class LineJoinRadioButton : RadioButton
    {
        public PenLineJoin LineJoinTag { set; get; }
    }
}
