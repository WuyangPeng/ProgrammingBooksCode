Exercises 16.1 and 16.2

1. Adding the menu item and toolbar button for the ellipse type is the samer procedure as
   for the exercises in Chapter 15.

2. You can create the CEllipse class as an analog of the CCircle class. The ellipse class
   constructor is simpler - you only have to create the rectangle for the ellipse from
   the two points passed to the constructor. The function to draw the ellipse is exactly the same as
   drawing a circle.

3. To allow an ellipse to be created, you only have to modify the CreateElement() function that is
   defined in the CSketcherView class.

Exercise 16.3

1. How the ellipse is drawn is determined by the CEllipse class. The draw() function in the class
   determines how the ellipse is drawn using the data set up in the constructor. You only need to change
   the constructor to arrange that the rectangle that encloses the ellipse is created on the assumption
   that the start point that is passed to the constructor is the center of the ellipse and the end point
   defines a corner of the enclosing rectangle.  The Offset() member of the CPoint class can help you
   to calculate the opposite corner to the end point. The code also shows how you can create the enclosing
   rectangle directly.

Exercises 16.4, 16.5, and 16.6

1. You add the new Pen Style menu in  the same way as the others. Choose IDs such that the event handler names
   will not be unduly long.

2. To implement drawing using different line types, all the shape class constructors must be modified to allow the line
   style to be specified when a shape in created. You can add a member m_LineStyle of type int to record the line style.
   The draw() functions for the shapes must be changed to set the appropriate line style when the pen is created.
   The line type to be used for drawing is set when you create a Pen object. You will need to record the currently selected
   line style in the document object. You can use the pen style constants that are of type in to record different line style
   so you just need to add a m_LineStyle member of type int to CSketcherDoc and set it appropriately in the Command event handlers
   for the items in the new menu. You will also need a member function that will allow a CSketcherView object to access the current
   line style.
   You will also have to modify the CreateElement() function in the CSketcherView class to pass the current line style to the
   constructor for the shape to be created.

Exercises 16.7 and 16.8

1. You add the Ellipse menu item and toolbar button in the Design view for form1. The first coding step is to add ELLIPSE an
   an enumerator to the ElementType enumeration.
   Add a Click event handler for the Ellipse menu item that sets the elementType member to ELLIPSE. Modify the
   elementToolStripMenuItem_DropDownOpening() function to check the Ellipse menu item when the element type is ELLIPSE.
   Make the Click event handler for the ellipse toolbar button the same as for the menu item.
   Modify the SetElementTypeButtonState() function to set the state for the ellipse toolbar button.
   To support drawing an ellipse, add an Ellipse class. It will be similar to the Circle class. Ensure that the position
   is set to be the top-left corner of the rectangle, regardless of how the ellipse is drawn. You also must ensure that
   the width and height are positive values. 
   To draw an ellipse, add a new case to the switch statement in the Form1_MouseMove() handler in the Form1 class.

2. There are many different ways to implement the line style capability. I added an enum to define the three line styles and 
   a private member of type LineStyle in the Form1 class, initialized to SOLID in the constructor, to record the current line style.
   The current line style is set in the Click event handlers for the Line Style menu items.
   The constructor for each shape class has an additional parameter of type LineStyle to specify the linestyle for the shape.
   The pattern array is selected by the GetPattern() function that I added to the Element class.
   Don't forget to add a function to the Form1 class to set the line style buttons state. This should be called in the Click
   event handlers for the line style menu items and in the Form1 constructor to set things up at the outset.

