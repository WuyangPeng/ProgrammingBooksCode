Exercise 19_01

1. If you understand what the CPrintData class provides, this is trivial.

Exercise 19_02

1. To scale text you have to sove two problems. 

2  The first is how you scale the text, and the hint gives you a clue how as to how you can do that. You have to decide on
   a font size that will apply for drawing a text object at scale 1, and adjust the font size in proportion to the scale factor.

3. The second problem is how the CText object discovers the current view scale. A simple way to do this is 
   to pass the current view scale to the Draw() function for a text object. This means though that you must modify the
   signature of the Draw() function in each of the other shape classes, otherwise you won't be able to call the Draw()
   functions polymorphically.

4. Of course, if you change the signature of the Draw() functions, all the calls to those functions must be changed too...

Exercise 19_03

1. The ColorDialog class makes this relatively easy, once you have created the menu item and toolbar button. You can
   use the Designer to drag a ColorDialog object onto the form from the Toolbox, or you can create a ColorDialog object
   yourself in the code.

Exercise 19_03
1. To create this line style you need to set the DashStyle proerty for a Pen object to Custem, then set the DashPattern
   property to a floating-point array of values that specifies the pattern that you want. I chose to do this in the
   constructor for each type of element. If you wanted several custom line styles, you would need to develop a more
   general approach.
   
   Note that line styles do not work with curves because they are drawn as a series of very short line segments.