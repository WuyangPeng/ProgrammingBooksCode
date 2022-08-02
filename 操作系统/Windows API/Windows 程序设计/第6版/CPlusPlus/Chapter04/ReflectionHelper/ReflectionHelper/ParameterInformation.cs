using System.Reflection;

namespace ReflectionHelper
{
    public sealed class ParameterInformation
    {
        ParameterInfo parameterInfo;

        // Public constructor required
        public ParameterInformation()
        {
        }

        internal ParameterInformation(ParameterInfo parameterInfo)
        {
            this.parameterInfo = parameterInfo;
        }
    }
}
