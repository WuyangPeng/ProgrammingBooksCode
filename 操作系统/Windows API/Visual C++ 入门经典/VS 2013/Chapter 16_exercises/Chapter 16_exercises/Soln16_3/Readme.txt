Solutions to Exercise 3 in Chapter 16


-I started with the Sketcher version that is the solution to Exercise 16_2. Using a combobox is very similar to using a list box. The creation of entries in the combobox is exactly the same.

-Deleted the list box and added a combobox to the dialog with the ID IDC_PENWIDTH_COMBO. Made the combobox wide enough to accommodate the longest list entries "Pen width 0.01 inches".

-Deleted m_PenWidth from CPenDialog.

-Added a value control variable for the combobox resource in the dialog with the name m_PenWidth and with min and max values of 0 and 5 respectively.

Modified OnInitDialog() to refer to the combobox instead of the list box.




