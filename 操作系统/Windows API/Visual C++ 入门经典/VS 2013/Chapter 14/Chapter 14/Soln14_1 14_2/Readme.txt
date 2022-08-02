Solution to Exercise 1 in Chapter 14

-Defined the CEllipse class derived from CElement.

-Added the Ellipse menu item to the Element menu in Sketcher.rc through Resource View with the ID ID_ELEMENT_ELLIPSE.

-Added an ellipse toolbar button to the IDR_MAINFRAME toolbar resource with the ID the same as for the menu item.

-Added the ELLIPSE enumerator to the definition for ElementType enumeration. 

-Added and implemented COMMAND_UI and UPDATE_COMMAND_UI handlers.

-Added an #include directive for Ellipse.h to SketcherView.cpp.

Solution to Exercise 2 in Chapter 14

-Modified the CreateElement() member of CSketcherView by adding a case to create a CEllipse object when  the element type is ElementType::ELLIPSE.

-Implemented the Draw() member of the CEllipse class . 


