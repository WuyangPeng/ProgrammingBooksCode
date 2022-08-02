Exercise 20_01

1. I created this as an SDI project on the assumption that you would only want to view
   one sketch at a time.
 
2. You need to copy ExtDLLExample.dll and the associated .lib file to the viewer project. I put the DLL
   in Soln20_01\Debug and I put the .lib file in Soln20_01\Soln20_01\Debug. I could then reference 
   the .lib by a relative path, Debug\ExtDLLExample.lib for the linker input Additional Dependencies property

3. I added the OnPrepareDC() override to the view class and used that to set up the DC so the entire sketch
   always displays in the client area of the window. I used the MM_ISOTROPIC mapping mode to ensure that the
   sketch displayed without distortion.