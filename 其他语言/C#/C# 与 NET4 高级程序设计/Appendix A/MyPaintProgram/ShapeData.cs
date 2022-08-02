using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace MyPaintProgram
{
  [Serializable]
  class ShapeData
  {
    // The upper left of the shape to be drawn.
    public Point UpperLeftPoint {get; set;} 

    // The current color of the shape to be drawn.
    public Color Color { get; set; } 

    // The type of shape.
    public SelectedShape ShapeType { get; set; } 
  }
}
