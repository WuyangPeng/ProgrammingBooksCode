Solutions to Exercise 2 in Chapter 17


-I started with the the solution to Exercise 1 in Chapter 17. 

-To scale text you must adjust the point size of the font to correspond to the view scale in effect when the text is drawn.

-You can do this either by making a CText object know about the drawing scale, or you can adjust the font in effect in the CDC object in the CSketcherView::OnDraw() function when the element being drawn is a CText object. I chose the latter approach.

-If you want the text elements to move nicely, you have to set the font size when you are moving a text element in CSketcherView::MoveElement().

  



