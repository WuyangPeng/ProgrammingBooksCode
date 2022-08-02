using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Shapes
{
    #region Shape base class
    // The abstract base class of the hierarchy.
    abstract class Shape
    {
        public Shape(string name = "NoName")
        { PetName = name; }

        // A single abstract method.
        public abstract void Draw();

        public string PetName { get; set; }
    } 
    #endregion

    #region Circle class
    // If we did not implement the abstract Draw() method, Circle would also be
    // considered abstract, and would have to be marked abstract!
    class Circle : Shape
    {
        public Circle() { }
        public Circle(string name) : base(name) { }
        public override void Draw()
        {
            Console.WriteLine("Drawing {0} the Circle", PetName);
        }
    } 
    #endregion

    #region Hexagon class
    // Hexagon DOES override Draw().
    class Hexagon : Shape
    {
        public Hexagon() { }
        public Hexagon(string name) : base(name) { }
        public override void Draw()
        {
            Console.WriteLine("Drawing {0} the Hexagon", PetName);
        }
    } 
    #endregion

    #region ThreeDCircle class
    // This class extends Circle and hides the inherited Draw() method.
    class ThreeDCircle : Circle
    {
        // Hide any Draw() implementation above me.
        public new void Draw()
        {
            Console.WriteLine("Drawing a 3D Circle");
        }

        public new string PetName { get; set; }
    } 
    #endregion
}
