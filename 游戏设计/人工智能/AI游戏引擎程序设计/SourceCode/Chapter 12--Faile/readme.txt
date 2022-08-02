     __        __           __                         __
    / /\      / /\         / /\                       / /\
   / / /     / /  \       / / /                      / / /
  / / /_    / / /\ \     / / /       __             / / /_
 / / / /\  / / /-/  \   / /  \  _   /_/\      _    / / / /\__
/_/ / / / /_/ / / /\ \ /_/ /\ \/ /\ \ \ \    / /\ /_/ / / / /\
\ \ \/ /  \ \ \/ /__\/ \_\/\ \ \/ /  \ \ \  / / / \ \ \/ / / /
 \ \  /    \ \  /           \_\  /    \ \ \/ / /   \ \  / / /
  \ \ \     \ \ \           / / /      \ \ \/ /     \ \ \/ /
   \ \ \     \ \ \         /_/ /        \ \  /       \ \  /
    \_\/      \_\/         \_\/          \_\/         \_\/

----------------------------------------------------------
Faile version 1.4
Readme.txt
Author: Adrien Regimbald
E-mail: adrien@ee.ualberta.ca
Web Page: http://www.ee.ualberta.ca/~adrien
Faile's Page: http://faile.sourceforge.net
----------------------------------------------------------

----------------------------------------------------------
INSTALLATION

Faile is covered by the MIT license, you can read about it in the file
license.txt which should have come with this distribution.

For the installation, I will assume you will be using Faile with
Winboard (see section on Graphical Interface).

If you downloaded the file faile14.zip, create a directory for Faile (I will
assume c:\faile14), and extract all files from faile14.zip into Faile's
directory.  If you wish to use Faile with the graphical interface WinBoard,
please read the "GRAPHICAL INTERFACE MODE" section below.  If you don't wish
to use WinBoard, you should read the "COMMAND LINE MODE" section below.

If you downloaded the file faile_1_4_4.tar.gz, you will need to compile the
program on your own.  There are 3 sample makefiles:
- "makefile" for use with MSVC++ 6.0
  To build: nmake
- "makefile.ppro" also for use with MSVC++ 6.0 but optimized for Pentium Pro
  and above CPUs
  To build: nmake -f makefile.ppro
- "makefile.gcc" which should be sufficient for most *NIX systems
  To build: make -f makefile.gcc

Faile should compile using most compilers.  If you have any difficulties,
please e-mail me.
----------------------------------------------------------

----------------------------------------------------------
GRAPHICAL INTERFACE MODE

Faile currently does not have its own graphical interface.  However,
it does support the use of WinBoard as an interface.  To run Faile
with WinBoard, use the following command or make a shortcut for it for your
convenience (assuming you have WinBoard installed in c:\winboard):
c:\winboard\winboard.exe -cp -fd "c:\faile14" -fcp "faile.exe"

Faile will also work under Xboard.  Use a command such as the following to run
it under Xboard (assuming that Xboard is in your path, and you have Faile
compiled in $HOME/faile14)
xboard -cp -fd "$HOME/faile14" -fcp "./faile"

Faile suppors the issuing of commands after every game when on an ICS when
using WinBoard/Xboard - simply place the commands which you want issued in
the gameend.txt file!


Note: you will have to use WinBoard version 4.0 or better, or Faile
will not function correctly.  Faile should run with Xboard (versions 4.0 or
better).  If you wish to use Faile on an ICS with Xboard, you will need to have
built it with "configure --enable-zippy".

Not all WinBoard features are implemented yet, but more support is planned
for the next version.
----------------------------------------------------------

----------------------------------------------------------
COMMAND LINE MODE

I recommend using WinBoard / Xboard to play against Faile, but if for some
reason you are stuck using the command line version, there are some things
which you will need to know.

Faile will recognize almost any "reasonable" variant of SAN or coordinate
notation.

When you are using Faile, you can type "help" for a short description of the
commands, here is what you will see:

diagram/d: toggle diagram display
exit/quit: terminate Faile
go:        make Faile play the side to move
new:       start a new game
level <x>: the xboard style command to set time
  <x> should be in the form: <a> <b> <c> where:
  a -> moves to TC (0 if using an ICS style TC)
  b -> minutes per game
  c -> increment in seconds
nodes:     outputs the number of nodes searched
nps:       outputs Faile's NPS in search
perft <x>: compute raw nodes to depth x
post:      toggles thinking output
xboard:    put Faile into xboard mode
----------------------------------------------------------

----------------------------------------------------------
FEATURES

Faile is an expert to master strength chess program, depending upon
the machine you run it on, and it's FREE!

I also hope that Faile will be useful to those trying to make their own chess
program, or are simply curious as to how one works.  Faile's source is
relatively small, while at the same time being full featured, neatly
coded, and well documented.
----------------------------------------------------------

----------------------------------------------------------
HASH OPTIONS

By default, Faile uses ~ 8MB of hash size.  Faile will, in general, play
better with more hash allocated.  However, you must be careful, as if you
specify more hash size than your machine can handle, Faile will be using
virtual memory, accessed from your hard drive, and performance may actually
suffer severely.  You can change the amount of hash which Faile will use
like this:
faile -hash <size in MB>

So to use 32MB of hash, you would do the following:
faile -hash 32


Note: the actual amount of RAM used by Faile may be slightly smaller than
what you specified, because Faile may not be able to evenly allocate up to
that much memory without going over the size specified.
----------------------------------------------------------

----------------------------------------------------------
OPENING BOOK

Faile's default book is based upon a collection of GM games, designed to cover
all ECO lines.

To make your own opening book, first create a PGN file of all of the games
which you wish to make the opening book for.  Please clean up the PGN file
before giving it to Faile, as Faile's PGN parser can't handle comments/
variations/NAGs/etc.  I suggest to clean it up that you use extract like this:
extract -C -N -V -s -o<output PGN file> <input PGN file>

After you have your desired PGN file, use Faile on it like this:
faile -mbook <PGN input file> [<max ply>]

The max ply is optional, and will be set to 20 if you don't set it to any
value.  The largest allowed max ply value is 40.  The output file will be
faile.obk and if you wish to keep a copy of an old faile.obk, make sure to back
it up before making a new opening book, as the old one will be overwritten if
it is not.

An example of creating a 30 ply book with the file games.pgn:
faile -mbook games.pgn 30

Please note that while creating an opening book, Faile will use up to 32MB of
RAM.  The process may also take a long time depending on how large of an
input file you use, and how fast your computer is.

Feel free to make your own opening book for Faile, and be sure to contact me
if you create an interesting book - I may even put it up on Faile's web page
if I think it is a nice book!
----------------------------------------------------------

----------------------------------------------------------
CURRENT WORK

I am not yet finished with Faile, and I will still be working on it for
some time to come.  Some of thing things that you may see in future versions:

- more WinBoard support
- a slightly improved evaluation function
- more opening book support, perhaps learning
- pondering
- some improvements on the search algorithm
- Faile's own user interface (not too sure on this one..)
----------------------------------------------------------

----------------------------------------------------------
FICS

You can use Winboard to have an account for Faile on FICS!!  Please
see the winboard documentation for how to do this.  If you do make
an account on FICS, please let me know! :)  Before you get an account on
FICS, be sure to read all of the appropriate documentation on FICS, such 
as "help computers" and "help computer_app"
----------------------------------------------------------

----------------------------------------------------------
DEDICATION & THANKS

The following people (in alphabetical order) have helped me out tremendously
over the time I've spent working on Faile, whether it was general programming
help when I was learning how to code, suggestions for search techniques,
bug detection/testing, etc.

Yngvi Bjornsson
Dann Corbit
Andrew Dados
Stefan Hildingstam
Marcel van Kervinck
Carsten Kossendey
David Lee
Gian-Carlo Pascutto
Matthew Shoemaker
Sam Slutzky
Brian Wickman

I am dedicating Faile to David Lee, who constantly encouraged me to keep
improving Faile, was always helping me out whenever I needed someone to do
test games/opening books/etc, and was also always there for me when I was
having personal problems.  I couldn't have done it without you Dave!
----------------------------------------------------------

----------------------------------------------------------
BUGS

Faile seems to be relatively bug-free, but if you notice any bugs, be
sure to contact me!

There are some potential trouble spots though:
- Faile may take a while to check for input during search, or it may not
be able to at all if you have defined #ANSI and recompiled Faile yourself.
If you are using the pre-made version of Faile, please wait a moment or two
after resetting the game before starting a new one.
- There are a number of unsupported WinBoard/Xboard features, these will
hopefully be supported in the future.

Faile is not perfect, but I hope that you enjoy it! :)
----------------------------------------------------------
