This folder contains all the sources of book.

It contatins project files for QtCreater IDE. `BoostBook.pro` - is the main project file.
See config.txt file for setupping platform specific flags.

All source code is distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


NOTE:
Primary goal of source codes in this folder is to teach. It is breaking some of the 
good C++ coding styles:

    * Headers are not always included in the beginning of source and header files.
    This is done in attempt to show in which header which classs and functions
    are defined. Another goal of doing so, is to avoid errors, while copying parts
    of code to book (it is simpler and safer to copy required peace of code at
    once, instaed of gathering together headers and code lines all across the project)

    * Our own classes are declared in global namespace (instead of separate namespace)
    This is done to reduce amount of unrequired code in book.

    * Usually no aliases for namespaces used and usually no `using namespace` used.
    This is done for your simplicity. You may open any recipe, start it from the
    middle of 'How to do it' part and see a working part of code that does not
    require searching all around the chapter for an answer 'What is a inter:: namespace?'.

