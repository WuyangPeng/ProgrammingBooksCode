Solutions to Exercises in Chapter 15


Exercise 1. Add the Ellipse menu item to the Element menu in Sketcher.rc through Resource View.

Exercise 2. Add a Command handler for the Ellipse menu item to the CSketcherDoc class by right-clicking the menu item
            and selecting Add Event Handler... from the popup. Implement the handler in the same way as for the other Element menu items.
            You must add the ELLIPSE enumerator to the definition for ElementType enumeration. Add and implement an UPDATE_COMMAND_UI handler
            in the same way.

Exercise 3. To provide toolbars buttons corresponding to the Ellipse menu item, edit the IDR_MAINFRAME and IDR_MAINFRAME_256 toolbar resource
            to add an ellipse button for each. Change the ID for each button to ID_ELEMENT_ELLIPSE.This associates the buttons with the Ellipse menu item.
            You can position the buttons by dragging them with the mouse to a suitable place in the toolbar - alongside the Circle toolbar button.
            To add tooltips for the buttons, add the tooltpi text as the value for the PRompt property for either button.

Exercise 4. What you see displayed as the text for a menu item is the value for the Caption property. This exercise thus requires 
            you to set the Caption property value in the UPDATE_COMMAND_UI handlers for the Color menu items according to whether
            or not they are currently selected. You can do this by calling the SetText() member for the CCmdUI object that is
            passed to the update handler.

Exercise 5. Add the Ellipse menu item to the Element menu in the Design view for the form. 
            Add ELLIPSE to the ElementType enumeration definition then double-click the Ellipse menu item to add the Click event handler.
            The handler is implemented in the same way as the others.
            Modify the elementToolStripMenuItem_DropDownOpening() function to deal with the Ellipse menu item.
            Add a bitmap resource that represents an ellipse with the ID IDB_CURVE to app.rc and change the filename to ellipse.bmp.
            Add a toolbar button in Design view for the form with the (Name) property as toolStripEllipseButton.
            Change the ImageTransparentColor property value to White and the Text property value to Ellipses.
            Select the Click event handler (in the property window for the toolbar button) to be the same as for the Ellipse menu item.
            Modify the SetElementTypeButtonState() function to deal with the ellipse button.
 