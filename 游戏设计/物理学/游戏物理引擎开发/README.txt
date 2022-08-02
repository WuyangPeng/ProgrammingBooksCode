Cyclone Physics System..

Copyright (c) Ian Millington 2003-2006. All Rights Reserved.

This software is distributed under licence. Use of this software
implies agreement with all terms and conditions of the accompanying
software licence.

Copyright (c) IPR Ventures 2003-2006. All Rights Reserved.

Please see accompanying LICENSE file.


Latest version
==============

Before using this source code you are _strongly_ recommended to visit
the www.procyclone.com website and download the latest version of the
code and demos. Via this website you also have access to a
browsable source code repository where you can see and download the
latest code as it changes, keep up to date with bug-fixes, and see
a history of the source code to find where things have been modified.

With the way stuff changes, it is likely that by the time you read
this book, the code will have been upgraded significantly, so visiting
the website it really a must!


Installation
============

The code can be extracted to any directory.


Building
========

The code is provided with build files compatible with Microsoft Visual
Studio .NET 2003 or later. They are contained in the build
directory. The 'cyclone' solution file contains all the demonstrations
and dependencies.


Layout
======

The build process creates a statically linked library in ./lib which
can be used with the include headers in ./include. The demo programs
are built and placed in the ./bin directory.

Source code is contained in the ./src directory.


Documentation
=============

The source code is heavily documented, and the contents correspond to
the discussion in the "Game Physics Engine Design" book.

Demos
=====

To run the demos you will require OpenGL and GLUT installed on your
machine, and the relevant DLLs or shared objects on the path.


Required Libraries
==================

To compile or run the demos, you'll need to have a copy of the OpenGL 
Utility Toolkit (GLUT) installed. You may already have this installed 
on your machine.

Included on the CD is glut32.dll. If you do not already have this file, 
you can install it in your c:/windows/system32 directory.

To compile the demos, you'll also need the headers and libraries for 
GLUT. These are available online at: 
http://www.xmission.com/~nate/glut.html for Windows PC, from the apple 
developer site for Mac OSX, and through your package manager for Linux 
installs.
