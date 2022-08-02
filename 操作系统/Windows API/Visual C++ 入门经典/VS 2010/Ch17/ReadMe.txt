Exercise 17_01

1. You change the container in the CCurve class to type list<CPoint>. You need to #include the list header in Elements.h.
   The CCurve constructor then should be changed to use the push)front() member of the list to add the points.
   Obviously the AddSegment() function must also use puh_front() to add a new point to the curve.
   The points in the list are in reverse order with the last point at the begining. You must therefore change the Draw() function
   to go through the list in reverse order when drawing the segments of the curve.

Exercise 17_02

1. This seems like a small change from the previous solution but there's more to it than meets the eye. 
   The container should now be of type list<CPoint*>.

2. You can change the point parameters for the CCurve constructor and the AddSegment() function to pointers instead of const references.
   You store the address of each point in the vector instead of the CPoint object in both the constructor and the AddSegment() function.
   Because the constainer stores pointers, you must dereference an iterator twice. The first dereference gets to the pointer and
   the second gets the point object.

3. Because the constructor and AddSegment() function signatures have changed, you must also change the calls in the CreateElement() member
   of CSketcherView and the mouse move handler. You must also remove the const qualifier from CreateElement(), otherwise passing pointers
   to the constructor will prevent the code from compiling.

4. Another complication is that you cannote just pass the addresses of m_FirstPoint
   and m_SecondPoint to the CCurve constructor and the AddSegment() function. Each time the mouse move handler is called, m_SecondPoint is 
   overwritten by a new point. The CCurve object needs all the defining points to continue to exist until it is destroyed.
   You must create new points on the heap to have a curve created properly.
   Of course, you must also implement the CCurve destructor so that it will release the heap memory occupied by the points.

Exercise 17_3
1. This exercise is designed to encourage you to explore the MFC containers.
   CArray is an MFC container that represents an array that can grow automatically.
   It is important that you call SetSize() for the container, otherwise memory reallocations will occur frequently
   which will slow operations.
   I added a member to the CCurve class to record the number of points stored in the container.
   You need to change the constructor, the AddSegment() function and the Draw() function to use the CArray container.

Exercise 17_4
1. To change the color of a shape element, you need to provide a way of updating the color member of the base class, Element.
   Once you have that it is easy to add a menu item to the context menu to change the color. I chose to do this by adding a property
   to the Element class.

2. The context menu is the place to put the capability to change the color of an element because through the highlighted element,
   you know which element you are dealing with. I added a Change Color menu item. Don't forget that you need to update the opening event
   handler for the context menu to get your new menu item displayed.
   
3. Of course, you have to provide a way to select the new color. Once you have that you can just use the color update mechanism and redraw
   the element. You could use a dialog when the context menu item is click but I chose to use a drop down menu that displays when
   the Change Color menu item is clicked. I implemented the opening event handler for the drop down menu to highlight the current
   element color. I added a helper function, setColor(), to the Form1 class and called that from the Click event handlers for the
   drop down menu items that select a new color.