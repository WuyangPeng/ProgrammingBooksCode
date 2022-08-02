using System;
using System.Reflection;

namespace ReflectionHelper
{
    public sealed class PropertyInformation
    {
        PropertyInfo propertyInfo;

        // Public constructor required
        public PropertyInformation()
        {
        }

        internal PropertyInformation(PropertyInfo propertyInfo)
        {
            this.propertyInfo = propertyInfo;
        }

        public string Name
        {
            get
            {
                return propertyInfo.Name;
            }
        }

        public Type PropertyType
        {
            get
            {
                return propertyInfo.PropertyType;
            }
        }

        public object GetValue(object obj)
        {
            return propertyInfo.GetValue(obj);
        }

        public void SetValue(object obj, object value)
        {
            propertyInfo.SetValue(obj, value);
        }
    }
}
