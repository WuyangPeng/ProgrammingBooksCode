Exercise 18_01

1. You can add radio buttons to the existing scale dialog but first you must remove the existing controls
   from the dialog. Display the scale dialog resource and delete the edit, spin, and static text controls.

2. Deleting resource does not remove the code from the scale dialog class that works with them so you
   must also remove the code that references the old controls, including that in the DoDataExchange() function.

3. Add the 8 radio buttons to a group box in the scale dialog resource. You can give them useful IDs such as IDC_SCALEn
   where n is the scale value.

4. Initialize the m_Scale member of the dialog class to 1 in the constructor.

5. To make sure the radio buttons are checked correctly, add code to the OnInitDialog() function.

5. To record which button is clicked you must add an BN_CLICKED event handler for each of the radio buttons
   that updates the m_Scale member of the dialog appropriately. The scale is retrieved from the dialog
   in the same way as before.

Exercise 18_02

1. The first step is to remove the radio  resources from the pen width dialog resource.

2. Now you must remove references to the deleted radio buttons from the CPenDialog class, including the message
   handlers for the radio buttons. Don't forget to delete the entries from the message map. You can also remove
   the m_PenWidth member of the class.

3. Now you can add a list box to the pen dialog resource and give it a suitable ID. Add m_PenWidth as a control variable
   for the list box of type int. Select value as the type and you can set limits for it if you wish. This will ensure 
   the variable gets set through the DDX mechanism.

4. Initialize the list box in the InitDialog() function for the pen width dialog.

Exercise 18_03

1. This is similar to the previous exercise because a combo box works in a similar way.You add the strings that are to be 
   displayed in exactly the same way.
   You set the Type property for the combo box resource to Drop List to get a drop down list.
   To display the complete list in the drop down, you need to extend the length of the drop down in the editor window
   by clicking the drop down arrow and dragging the bottom edge down a suitable distance.
   You must remember to set the Sort property to Flase, otherwise the list won't be in the right sequence.