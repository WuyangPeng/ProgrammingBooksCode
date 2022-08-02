using System;
using System.Collections.Generic;
using System.Reflection;

namespace ReflectionHelper
{
    public sealed class AssemblyInformation
    {
        Assembly assembly;

        public AssemblyInformation(Type sampleType)
        {
            assembly = sampleType.GetTypeInfo().Assembly;
        }

        public IEnumerable<TypeInformation> ExportedTypes
        {
            get
            {
                foreach (Type type in assembly.ExportedTypes)
                {
                    yield return new TypeInformation(type);
                }
            }
        }
    }
}
