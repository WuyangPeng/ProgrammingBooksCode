Solutions to Exercise 1 in Chapter 16


-I started with the Sketcher version 2 in code from the book, consequently the scale is not displayed in the status bar for a view.

-Deleted the spinner and buddy from the IDD_SCALE_DLG dialog resource, just leaving the buttons in the dialog.

-Deleted all references to the spinner from the CScaleDialog class and the implementation of its members in  the .cpp file.

-Added a group box containing 8 radio buttons to the scale dialog resource. Implemented event handlers for the radio buttons in the CScaleDialog class to set the m_Scale member to the appropriate value.

-Added code to initialize the radio buttons in the OnInitDialog() member of CScaleDialog.


