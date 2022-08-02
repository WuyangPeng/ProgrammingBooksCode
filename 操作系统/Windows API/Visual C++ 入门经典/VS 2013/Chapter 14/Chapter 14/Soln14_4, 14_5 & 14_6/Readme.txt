Solutions to Exercises 4, 5, and 6 in Chapter 14


-Added a menu to the IDR_SketchTYPE menu bar for line styles.

-Added a menu item for each line style to the Line Style menu.

-Added a lineStyle member of type int to CSketcherDoc to record the current line style. The value in lineStyle will be
 one of the PenStyle enumeration values accepted by the CPen constructor so its default value is PS_SOLID.

-Added a GetLineStyle() member to CSketcherDoc to return the current pen style.

-Added COMMAND_UI and COMMAND_UPDATE_UI handlers in CSketcherDoc for the line style menu items.

-Added an extra parameter to the element constructors for the pen style.

-Updated the CreateElement() member of CSketcherView to pass the pen style to the element constructors. 
 This required a value for the pen width to be passed in addition.

-Added a lineStyle member to CElement.

-Updated the CreatePen() member of CElement to use the line style.




