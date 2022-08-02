using System.Reflection;
using System.Runtime.InteropServices.WindowsRuntime;

namespace ReflectionHelper
{
    public sealed class ConstructorInformation
    {
        ConstructorInfo constructorInfo;

        // Public constructor required
        public ConstructorInformation()
        {
        }

        internal ConstructorInformation(ConstructorInfo constructorInfo)
        {
            this.constructorInfo = constructorInfo;
        }

        public bool IsPublic
        {
            get
            {
                return constructorInfo.IsPublic;
            }
        }

        public ParameterInformation[] GetParameters()
        {
            ParameterInfo[] parameterInfo = constructorInfo.GetParameters();
            ParameterInformation[] parameterInformations = new ParameterInformation[parameterInfo.Length];

            for (int i = 0; i < parameterInfo.Length; i++)
                parameterInformations[i] = new ParameterInformation(parameterInfo[i]);

            return parameterInformations;
        }

        public object Invoke([ReadOnlyArray] object[] parameters)
        {
            return constructorInfo.Invoke(parameters);
        }
    }
}
