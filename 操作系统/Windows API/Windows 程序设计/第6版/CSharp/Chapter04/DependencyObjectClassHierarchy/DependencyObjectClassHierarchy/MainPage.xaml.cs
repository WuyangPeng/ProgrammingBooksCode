using System;
using System.Collections.Generic;
using System.Reflection;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Documents;
using Windows.UI.Xaml.Media;

namespace DependencyObjectClassHierarchy
{
    public sealed partial class MainPage : Page
    {
        Type rootType = typeof(DependencyObject);
        TypeInfo rootTypeInfo = typeof(DependencyObject).GetTypeInfo();
        List<Type> classes = new List<Type>();
        Brush highlightBrush;

        public MainPage()
        {
            this.InitializeComponent();
            highlightBrush = new SolidColorBrush(new UISettings().UIElementColor(UIElementType.Highlight));

            // Accumulate all the classes that derive from DependencyObject 
            AddToClassList(typeof(Windows.UI.Xaml.DependencyObject));

            // Sort them alphabetically by name
            classes.Sort((t1, t2) =>
                {
                    return String.Compare(t1.GetTypeInfo().Name, t2.GetTypeInfo().Name);
                });

            // Put all these sorted classes into a tree structure
            ClassAndSubclasses rootClass = new ClassAndSubclasses(rootType);
            AddToTree(rootClass, classes);

            // Display the tree using TextBlock's added to StackPanel
            Display(rootClass, 0);
        }

        void AddToClassList(Type sampleType)
        {
            Assembly assembly = sampleType.GetTypeInfo().Assembly;

            foreach (Type type in assembly.ExportedTypes)
            {
                TypeInfo typeInfo = type.GetTypeInfo();

                if (typeInfo.IsPublic && rootTypeInfo.IsAssignableFrom(typeInfo))
                    classes.Add(type);
            }
        }

        void AddToTree(ClassAndSubclasses parentClass, List<Type> classes)
        {
            foreach (Type type in classes)
            {
                Type baseType = type.GetTypeInfo().BaseType;

                if (baseType == parentClass.Type)
                {
                    ClassAndSubclasses subClass = new ClassAndSubclasses(type);
                    parentClass.Subclasses.Add(subClass);
                    AddToTree(subClass, classes);
                }
            }
        }

        void Display(ClassAndSubclasses parentClass, int indent)
        {
            TypeInfo typeInfo = parentClass.Type.GetTypeInfo();

            // Create TextBlock with type name
            TextBlock txtblk = new TextBlock();
            txtblk.Inlines.Add(new Run { Text = new string(' ', 8 * indent) });
            txtblk.Inlines.Add(new Run { Text = typeInfo.Name });

            // Indicate if the class is sealed
            if (typeInfo.IsSealed)
                txtblk.Inlines.Add(new Run 
                    { 
                        Text = " (sealed)", 
                        Foreground = highlightBrush 
                    });

            // Indicate if the class can't be instantiated
            IEnumerable<ConstructorInfo> constructorInfos = typeInfo.DeclaredConstructors;
            int publicConstructorCount = 0;

            foreach (ConstructorInfo constructorInfo in constructorInfos)
                if (constructorInfo.IsPublic)
                    publicConstructorCount += 1;

            if (publicConstructorCount == 0)
                txtblk.Inlines.Add(new Run
                {
                    Text = " (non-instantiable)",
                    Foreground = highlightBrush
                });

            // Add to the StackPanel
            stackPanel.Children.Add(txtblk);

            // Call this method recursively for all subclasses
            foreach (ClassAndSubclasses subclass in parentClass.Subclasses)
                Display(subclass, indent + 1);
        }
    }
}
