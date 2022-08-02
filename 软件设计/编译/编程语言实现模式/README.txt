This directory contains the source code for the Language
Implementation Patterns book. Feel free to change the sources and
experiment! Here's a description of what you'll find:

README.txt     		This file

antlr-3.2.jar		ANTLR 3.2 with ANTLR 2.7.7 and StringTemplate 3.2.1
stringtemplate-3.2.1.jar

build-macros.xml	ANT related files (see below)
build.properties
build.xml

These are the code subdirectories for the individual chapters (some of
the directories contain code for multiple chapters):

parsing			
IR
walking
symtab
semantics
interp		
trans

Here's a sample of how to build and run the register-based bytecode
interpreter manually (using the uber antlr-3.2.jar):

$ cd code/interp/reg
$ java -cp ../../antlr-3.2.jar org.antlr.Tool Assembler.g
$ javac -cp ../../antlr-3.2.jar *.java
$ java -cp .:../../antlr-3.2.jar Interpreter t.rcode 
9
$

If you put the jar into your CLASSPATH (from unix), life is much
easier:

$ export CLASSPATH="$CLASSPATH:/full-path-to-book/code/antlr-3.2.jar"
$ java org.antlr.Tool Assembler.g
$ javac *.java
$ java Interpreter t.rcode 
9
$ 

Enjoy!
Terence Parr, September 2009

-------------------------------------------------------------------------
How to use Ant to build the code samples for this book
By Martijn Reuvers -- Ant files and this description
(http://www.javalid.org to add validatation to your java objects)

All source code can be compiled, generated and executed using a few
Ant commands.

To get Ant: Download it from http://ant.apache.org and follow the
instructions on how to install it. Make sure that your JAVA_HOME
points at least to a JDK 1.5 or newer installation.

Commands available:

ant clean     -> Cleans entire project
ant generate  -> Generates all antlr source files (based on the grammars)
ant compile   -> Compiles everything (and generates)
ant run	      -> Executes all tests that Terence wrote
                 (and compiles and generates)

Each of these commands can be executed from *any* directory, when run
in the root it for instance compiles all projects. You can also run it
from e.g. sub-directory tree where it will compile all sub-projects of
the tree directory. Finally you can run all commands in each specific
project, for example inside tree/asm.
