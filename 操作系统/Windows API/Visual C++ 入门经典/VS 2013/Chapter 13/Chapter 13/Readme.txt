Exercises in Chapter 13
There is no code for solutions to these exercises becuase they just require operations with the IDE, which does the work. Here's what you need to do:

Exercise 1. Add the Ellipse menu item to the Element menu in Sketcher.rc through Resource View.

Exercise 2. Add a Command handler for the Ellipse menu item to the CSketcherDoc class by right-clicking the menu item
            and selecting Add Event Handler... from the popup. Implement the handler in the same way as for the other Element menu items.
            You must add the ELLIPSE enumerator to the definition for ElementType enumeration. Add and implement an UPDATE_COMMAND_UI handler
            in the same way.

Exercise 3. To provide a toolbar button corresponding to the Ellipse menu item, edit the IDR_MAINFRAME toolbar resource
            to add an ellipse button. Change the ID for the button to ID_ELEMENT_ELLIPSE.This associates the button with the Ellipse menu item.
            You can position the button by dragging it with the mouse to a suitable place in the toolbar - alongside the Circle toolbar button.
            To add a tooltip for the button, add the tooltip text as the value for the Prompt property for the button preceded by \n.

Exercise 4. What you see displayed as the text for a menu item is the value for the Caption property. This exercise thus requires 
            you to set the Caption property value in the UPDATE_COMMAND_UI handlers for the Color menu items according to whether
            or not they are currently selected. You can do this by calling the SetText() member for the CCmdUI object that is
            passed to the update handler.
