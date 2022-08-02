================
FLY3D SDK README
================

WEB:  http://www.fly3d.com.br
MAIL: info@fly3d.com.br


Requirements
============

   The Fly3D Engine requires win9x/Me/2k/Nt4 in order to run. 
   To develop new plug-ins/games with the engine you will need Visual C++. 
   A good 3D card supporting OpenGL is also required. 
   Make sure to be using the latest drivers available for your 3D card to get the best compatibility. 
   To get the best performance, TNT, TNT2, GeForce256 and GeForce2 based 3D cards are preferred.

   For running the FlyEditor.exe, you need latest MFC 4.2 files installed. 
   Many programs requires it, so you should already have it. 
   If the editor do not start up, download the mfc42.zip from our download page.

   For running the engine in a 3dfx1 or 3dfx2 card (no 3D window support) you need to download the 3dfxopengl.zip file from our download page and unzip it to the flysdk directory. 
   Then just run the 'Fly3D Menu' item from the installation icons. 
   3fdx3 or 3dfx Banshee cards do not require the opengl update as they all support standard OpenGL and windowed 3D. 


Contents
========

flyConfig.exe

   This is the configuration utility and must be run to select the desired video and render modes.

flyFrontend.exe

   This is the main front end executable. It will run any Fly3D plug-in(s) in OpenGL or direct3D, windowed or full screen.

   The following command line will run the menu.fly demo and set fullscreen:

   flyFrontend.exe menu/menu.fly -fullscreen

flyEditor.exe

   This is a frontend executable created with MFC view/doc architecture. It enables easy editing of .fly files by using a Windows explorer like Interface (tree view/list view/render view). With it you will be able to add/remove plug-ins, add/remove game elements from the plug-ins and also change any plug-in parameters while playing the game in real time. The editor uses OpenGL in the render view but a 3D card with windowed 3D must be used (3dfx and 3dfx2 based cards other then Banshee cannot do hardware 3D in a window).

   When using the editor with the demos, you must first unpack the demo files by using the tool menu option Unpak, and selecting the demo .fpk file desired.

flyServer.exe

   This is the console server front end. It is used to host multiplayer games (It runs the simulation, but does no rendering). To start up a Fly3D server use the following command line:

   flyServer.exe box/box.fly gamename

flyLight.exe

   This is a front end that computes lighting for a .bsp file specified in .fly script file. It generates the light maps file (.lmp) and precompute lighting wikth shadows for all static lights used in the level. It must be run after exporting a new level.

flyPVS.exe

   This frontend computes the pvs file for a bsp file. This application generates the leaf-leaf visibility information and takes a long time to execute. Should be run after exporting a new level.

/data

   This directory is where all data used in the levels needs to be placed (textures, objects, sounds, bsp and pvs). You can pack subdirectories from the data dir into a single pack file (.fpk) using the flypak.exe utility.

/lib

   This directory includes the Fly3D.lib and Fly3D.h files that need to be included in your custom plug-in projects. 

/plugin

   This directory includes several demo plug-ins with source code. Open the fly_plugin.dsw workspace file in Visual C++ (includes all plug-in projects).

/util

   This directory includes several utilities to be used with the engine.

The included utilities are: 

flyplugin.awx

   This is the Visual C++ wizard for creating new Fly3D plug-ins. See the flyplugin.hlp file for instructions on how to install and use it.

expflybsp2.dle and expflybsp3.dle

   These are the 3D Studio MAX 2.x and 3.x bsp export plug-ins. Copy it to the 3D Studio MAX plug-ins dir before opening 3D Studio MAX and a new type of file export will be availabe. Requires the Fly3D.dll in windows\system or 3D Studio MAX root dir.

impflybsp2.dli and impflybsp3.dli

   These are the 3D Studio MAX 2.x and 3.x bsp import plug-ins. Copy it to the 3D Studio MAX plug-ins dir before opening 3D Studio MAX and a new type of file import will be availabe. Requires the Fly3D.dll in path or 3D Studio MAX root dir.

flyfonts.exe

   Utility to generate a font texture map from any windows installed font.

flypak.exe

    Utility to pack and unpack directories from the data folder. 


Demo levels
===========

menu/menu.fly

   This is a demonstration implementing a 3D menu. 
   The menu_item objects execute console commands to implement their functionality. 
   Use the F1 key to return to the menu when running any other demo level.

   Use the following keys to move around:
   'UP' - move up
   'DOWN' - move down
   'ENTER' - select item
   'ESC' - console window

walk/walk.fly

   This is a q3test2 like demo. To run it, open the .fly file in the flyFrontend.exe application. 
   It implements a 'instagib' deathmatch arena for multiplayer games.

   Use the following keys to move around:
   'S','X' - move player forward/backward
   ARROWS - rotates the head
   ALT - slide
   'Q','E' - slide left/right
   'W' - headlight on/off
   SPACE - jump
   CTRL - fire
   ESC - console window
   MOUSE B1 - fire
   MOUSE B2 - zoom
   MOUSE MOV- rotates

box/box.fly

   This is a simple level demonstrating dynamic shadows and fog maps. 
   To create a multiplayer server game, run the following command line:

   flyserv.exe box/box.fly gamename

   To join a multiplayer game, use the join menu command (or Ctrl-J).
   Key commands are the same as the walk demo.

ship/ship_sp.fly - ship single player demo
ship/ship_mp.fly - ship multipayer demo

   This is a Descent/Forsaken like multiplayer demo. 
   To run it, open the .fly file with the fly.exe application. 
   To create a multiplayer server game, run the following command line:

   flyserv.exe ship/ship.fly gamename

   To join a multiplayer game, use the join menu command.

   Use the following keys to move around:
   'S','X' - move ship forward/backward
   ARROWS - rotates the ship
   ALT - slide
   'Q','E' - slide left/right
   'A','D' - bank left/right
   'W' - headlight on/off
   'C' - back camera on/off
   CAPSLOCK - afterburner
   '1'..'9' - select gun
   SPACE - fire selected gun
   ESC - console window

car/car.fly

   This is a landscape car race demo.

   Use the following keys to move around:
   'UP' - accelerate forward
   'DOWN' - accelerate backward
   'LEFT' - turn left
   'LEFT' - turn right
   'ESC' - console window

   To add a robot car, type 'activate car1' at the console. Repeat this command to add more cars to the race.

