using System.Collections.Generic;
using System.Reflection;
using Windows.UI;

namespace Petzold.ProgrammingWindows6.Chapter11
{
    public class NamedColor
    {
        static NamedColor()
        {
            List<NamedColor> colorList = new List<NamedColor>();
            IEnumerable<PropertyInfo> properties = typeof(Colors).GetTypeInfo().DeclaredProperties;

            foreach (PropertyInfo property in properties)
            {
                NamedColor namedColor = new NamedColor
                {
                    Name = property.Name,
                    Color = (Color)property.GetValue(null)
                };

                colorList.Add(namedColor);
            }

            All = colorList;
        }

        public static IEnumerable<NamedColor> All { private set; get; }

        public string Name { private set; get; }

        public Color Color { private set; get; }
    }
}
