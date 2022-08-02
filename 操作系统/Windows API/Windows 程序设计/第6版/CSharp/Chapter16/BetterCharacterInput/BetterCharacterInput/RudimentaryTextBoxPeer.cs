using Windows.Foundation;
using Windows.UI.Xaml.Automation;
using Windows.UI.Xaml.Automation.Peers;
using Windows.UI.Xaml.Automation.Provider;

namespace BetterCharacterInput
{
    public sealed class RudimentaryTextBoxPeer : FrameworkElementAutomationPeer, 
                                                 IValueProvider, ITextProvider
    {
        RudimentaryTextBox rudimentaryTextBox;

        public RudimentaryTextBoxPeer(RudimentaryTextBox owner)
            : base(owner)
        {
            this.rudimentaryTextBox = owner;
        }

        // Override
        protected override object GetPatternCore(PatternInterface patternInterface)
        {
            if (patternInterface == PatternInterface.Value ||
                patternInterface == PatternInterface.Text)
            {
                return this;
            }
            return base.GetPatternCore(patternInterface);
        }

        // Required for IValueProvider
        public string Value
        {
            get { return rudimentaryTextBox.Text; }
        }

        public bool IsReadOnly
        {
            get { return false; }
        }

        public void SetValue(string value)
        {
            rudimentaryTextBox.Text = value;
        }

        // Required for ITextProvider
        public SupportedTextSelection SupportedTextSelection
        {
            get { return SupportedTextSelection.None; }
        }

        public ITextRangeProvider DocumentRange
        {
            get { return null; }
        }

        public ITextRangeProvider RangeFromPoint(Point pt)
        {
            return null;
        }

        public ITextRangeProvider RangeFromChild(IRawElementProviderSimple child)
        {
            return null;
        }

        public ITextRangeProvider[] GetVisibleRanges()
        {
            return null;
        }

        public ITextRangeProvider[] GetSelection()
        {
            return null;
        }
    }
}
