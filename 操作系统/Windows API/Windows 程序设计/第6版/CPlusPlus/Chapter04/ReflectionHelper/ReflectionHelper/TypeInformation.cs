using System;
using System.Collections.Generic;
using System.Reflection;

namespace ReflectionHelper
{
    public sealed class TypeInformation
    {
        Type type;
        TypeInfo typeInfo;

        public TypeInformation(Type type)
        {
            this.type = type;
            typeInfo = type.GetTypeInfo();
        }

        public string Name
        {
            get
            {
                return type.Name;
            }
        }

        public bool IsPublic
        {
            get
            {
                return typeInfo.IsPublic;
            }
        }

        public bool IsSealed
        {
            get
            {
                return typeInfo.IsSealed;
            }
        }

        public TypeInformation BaseType
        {
            get
            {
                return new TypeInformation(typeInfo.BaseType);
            }
        }

        public IEnumerable<PropertyInformation> DeclaredProperties
        {
            get
            {
                IEnumerable<PropertyInfo> declaredProperties = type.GetTypeInfo().DeclaredProperties;

                foreach (PropertyInfo propertyInfo in declaredProperties)
                {
                    yield return new PropertyInformation(propertyInfo);
                }
            }
        }

        public IEnumerable<ConstructorInformation> DeclaredConstructors
        {
            get
            {
                IEnumerable<ConstructorInfo> declaredConstructors = type.GetTypeInfo().DeclaredConstructors;

                foreach (ConstructorInfo constructorInfo in declaredConstructors)
                {
                    yield return new ConstructorInformation(constructorInfo);
                }
            }
        }

        public bool IsAssignableFrom(TypeInformation derivedType)
        {
            return typeInfo.IsAssignableFrom(derivedType.typeInfo);
        }

        public PropertyInformation GetDeclaredProperty(string name)
        {
            return new PropertyInformation(type.GetTypeInfo().GetDeclaredProperty(name));
        }

        public override bool Equals(object obj)
        {
            if (obj == null || !(obj is TypeInformation))
                return false;

            return this.type.Equals((obj as TypeInformation).type);
        }

        public override int GetHashCode()
        {
            if (type == null)
                return 0;

            return type.GetHashCode();
        }
    }
}
