Solutions to Exercise 2 in Chapter 16


-I started with the Sketcher version that is the solution to Exercise 16_1.

-Deleted the pen width radio buttons and group box and added a list box to the dialog with the ID as IDC_PENWIDTH_LIST. Made the list box wide enough to accommodate the longest list entries "Pen width 0.01 inches".

-Deleted m_PenWidth from CPenDialog and all the handlers for the radio buttons(including the message map entries).

-Added a value control variable for the list box resource in the dialog with the name m_PenWidth and with min and max values of 0 and 5 respectively.

Modified OnInitDialog() to remove the old radio button initialization and added code to set up the strings in the list box.




