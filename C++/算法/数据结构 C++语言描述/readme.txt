Microsoft Visual C++ Users:

      Open directory  msvcpp

      Use the workspace/project "program.dsw". As a prototype,
      the project contains a program from Chapter 1. The graphics
      library is loaded in the project, so the project can
      be used both for programs that do and do not use the graphics
      package.

Other contents in the "ftsoftds" directory:

      All classes and libraries that are developed in the book are
      located as header files in the directory "include". 
      NOTE: You will need to add the "include" directory to
      the list of directories the compiler searches for include files.
 
      The programs that are developed in the book are located in
      the corresponding chapter directory (ch1 and so forth).

      The directory "ezdraw" contains the graphics library for 
      Microsoft Visual C++ (ezd32m.lib).

         The directory also contains a dynamic link library
         "ezdraw32.dll" that must reside in the Windows/System
         directory and the file "ezdraw.ini" that belongs in the
         Windows directory. It may be necessary to set Windows Explorer
         so it will view hidden and system files in order to see
         "ezdraw32.dll".

            Copy:      "ezdraw32.ini"  to "c:\Windows\"
            Copy:      "ezdraw32.dll"  to "c:\Windows\System"
