Readme.txt

If possible, you should print this file out first before you start the
installation process.



I. Installation instructions


A. Compiler

Before you can compile any programs, you'll have to install the
compiler. To do this, double-click "freecommandLinetools.exe" in the
directory on the CD where you found this "readme.txt" file, and
follow the instructions.

(Note that you don't have to register the compiler if you don't want
to, even though you'll have the opportunity to do so when you install
it.)


B. Code samples

Next, copy the "code" directory from the CD to your hard disk. You can
do this by dragging and dropping that directory from the CD to your
hard disk, wherever you want to put it. The instructions here assume
that you are putting the code directory on your C: drive, under the
"dialog" directory, so the exact location of the code directory is
"c:\dialog\code".

However, copying files from a CD via drag-and-drop leaves the files
"write protected", which means that you can't edit them. To fix this,
double-click on the "c:\dialog\code" directory that you have just
created on your hard disk, and then double-click on "unprot.bat". This
will make all the files in that directory writable, so you will be
able to edit them.


C. Debugger

Unfortunately, I was unable to include the debugger on the CD due to
our agreement with Borland, which covers only the compiler. Therefore,
you'll have to download and install it yourself. However, this is not
difficult. Point your browser at

http://www.borland.com/products/downloads/download_cbuilder.html

then click on "Turbo Debugger". You'll have to create an account
before you can download the debugger. Once you have downloaded it, you
can double-click on it to install it.


D. More compiler installation instructions

The following instructions on finishing the setup of the
compiler have been adapted from the Borland web page on installing the
compiler (http://community.borland.com/article/0,1410,21205,00.html).
If you didn't install the compiler on drive c, you'll have
to change the path and configuration file entries to point to the
drive where you installed the compiler.

1. Configuring the system environment:

Open a console box.
a.  Start | Run...
b.  Type "command" into the field [Enter]

* If Windows 95/98:
Navigate to the root in order to modify the PATH reference in the
  autoexec.bat file.
c.  Type "cd" [Enter]
d.  Type "edit autoexec.bat" [Enter]
e.  Insert a line and type "PATH=C:\BORLAND\BCC55\BIN;%PATH%"
f.  Save the changes (Alt-F then hit S).
g.  Exit edit. (Alt+F then press X).

* If Windows NT:
Add a path reference to the Environment variables:
c.  Using the mouse, right-click on the "My Computer" icon
  (on your desktop) and choose "Properties".
d.  Click on the "Environment" tab.
e.  Click on "Path" in the "System Variables" field.
f.  Highlight the "Path" System variable (bottom).
g.  Click in the "Value" field.
h.  Append the line with ";C:\BORLAND\BCC55\BIN;"
  (exactly 1 semi-colon between references)
i.  Click on the "Set" button.
j.  Click OK (in the "System Properties" window)

* Or, if Windows 2000/XP:
Add a path reference to the Environment variables:
c.  Using the mouse, right-click on the "My Computer" icon
  (on your desktop) and choose "Properties".
d.  Click on the "Advanced" tab.
e.  Click on the "Environment Variables..." button.
f.  Highlight the "Path" System variable (bottom).
g.  Click on the "Edit..." button.
h.  Append the line with ";C:\BORLAND\BCC55\BIN;"
i.  Click OK (in the "Edit System Variables")
j. Click OK (in the "Environment Variables" window)
  and click OK (in the "System Properties" window)

Navigating to the directory,"c:\Borland\bcc55\bin"
k. In the console box you opened in steps 1 and 2, type
cd borland\bcc55\bin [Enter]

2. Creating the configuration files:

Note: The command line in the console box should read:
C:\BORLAND\BCC55\BIN

Part 1: Creating BCC32.CFG.
a.  Type "edit bcc32.cfg" [Enter]  (This creates the file and opens a
blank window in the editor).
b. Add these lines:

    -I"c:\Borland\Bcc55\include"
    -L"c:\Borland\Bcc55\lib"

(You can copy and paste the above lines from readme.txt if you prefer)

c. Save the changes (Alt-F then hit S).
d. Exit edit. (Alt+F then press X).

Part 2: Creating ILINK32.CFG
e. Type "edit ilink32.cfg"  (This creates the file and opens a blank
window in the editor).
f. Add this line:

    -L"c:\Borland\Bcc55\lib"

(You can copy and paste the above line from readme.txt if you prefer)

g. Save the changes (Alt-F then hit S).
h. Exit edit. (Alt+F then press X).
i. Type "exit" [Enter]
j. Restart Windows (not needed in Windows 2000).

-----------------------------



II. Checking that the installation is successful


A. Initial check

Once you have installed the compiler and debugger and copied the
source code examples, you should check to make sure that you can
compile and run at least one of the programs. I have supplied batch
files to compile all the examples in each chapter, and a batch file to
compile all the examples in the entire book. I recommend that you
start by running the batch file that compiles the example from chapter
1, named "ch1.bat". To run this batch file, just open a command prompt
(or console box) window as in step I.D.1, switch to the "code"
directory where you installed the example programs on your hard disk,
and type "ch1". Assuming that you have copied the code to
C:\dialog\code, you should see the following text displayed,
indicating that the compiler is compiling the example program:

C:\dialog\code>compile ages

C:\dialog\code>bcc32 -v ages
Borland C++ 5.5.1 for Win32 Copyright (c) 1993, 2000 Borland
ages.cpp:
Turbo Incremental Link 5.00 Copyright (c) 1997, 2000 Borland

When the compilation finishes, you can type "ages" at the command
prompt. The program should ask you for two ages and report the
difference between the two ages.


B. Compiling the rest of the example programs

The code for each chapter can be compiled by typing in the name of the
batch file for that chapter. For example, to compile the sample
programs in chapter 3, switch to the "code" directory where you
installed the example programs on your hard disk, and type "ch3".


III. Writing and compiling your own programs

To write a program, open a text editor that only stores what you type
in, such as Notepad. DO NOT USE Word, Wordpad, or any other word
processing program that stores anything other than what you type. If
you do, your programs will not compile.

Type your code in, and save it as a file with the extension ".cpp", in
the "code" directory where you installed the example programs on your
hard disk. Then open a command prompt window, switch to the "code"
directory, and type "compile" followed by the name of your program. It
is not necessary to type the extension when compiling a program. For
example, if you were to write a program named "test.cpp", you would
compile it by typing "compile test" in the command prompt window. To
run the program, just type its name in the command prompt window (in
the "code" directory) without any extension. For example, for your
"test" program, you would just type "test".

IV. Debugging

One thing you should know before running the debugger: it doesn't work
very well if the command prompt window has a scrollbar; that is, if it
has more lines than will fit on your screen. You should change the
properties of your command prompt window so that it doesn't have a
scroll bar before trying to use the debugger. You can do this by right
clicking on the title bar of the command prompt window and selecting
"properties". Then select the "layout" and change the "height" value
until you see that the scroll bar on the right of the example screen
goes away.

To debug a program, type "td32" followed by the name of the program,
without adding any extension to the name of the program. For example,
to debug your "test" program, type "td32 test" in the command prompt
window in the "code" directory.

The debugger has quite a few functions, which I cannot describe here.
You should start by typing Alt-f to get to the help menu, then select
"help on help". That will give you some information on how to get
started with the debugger. If you get really stuck, you can always
type Alt-x to exit from the debugger.



V. Nonstandard functions

Here are the functions that you'll need to replace if you want to move
to another compiler:

Supplied with Borland compiler:
--------------
void clrscr();
void gotoxy();
void clreol();

Added by me:
--------------
int windos::getkey();
int windos::ScreenRows();
void windos::ScreenGetCursor(int *_row, int *_col);

A function that is likely to be supplied with any compiler,
but is not part of the C++ standard library:
--------------
int strnicmp( const char *string1,
const char *string2, size_t count);




