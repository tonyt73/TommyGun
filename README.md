
        Welcome to TommyGun
           Version 1.3
  (c) copyright 2004-2017 Tony Thompson

TommyGun is a retro development environment for creating ZX Spectrum games.

Contact Me:
===========
tommygun.ide@gmail.com
My name is TONY; not Tommy and not TommyGun.
TommyGun is the name of the application.


Pasmo Z80 Assembler
===================
http://pasmo.speccy.org/
Pasmo is used with permission from Julián Albo
Please see the Pasmo folder for open source licencing information

Portable Z80 emulator
=====================
(c) 2007 Marat Fayzullin
http://fms.komkon.org/EMUL8/


Quick Start Guide
=================
Want to see what TommyGun can do but without having to write any code or draw any artwork?
Then please read the Getting Started Guide.doc for how to run the SabreWulf project.

Whats New?
==========
1.3.8 (June 2017)
* Scorpio VCL Components
  * Removed all unusued components and their references from all plugins
* Core
  * Fixed dialog color
  * Changed folder dialog to use Windows Select Folder dialog
* Image Editor
  * Added ZX Spectrum Next 256 color palette support
  * Added check to not load duplicate palette plugins
* Code Editor
  * Added Scintilla syntax highligher colour editor
  * Added Move to other view for side by side editing like Notepad++
  

1.3.7 (January 2017)
Minor Release Revision
* Core
  o Removed registration due to continued issues with a DLL

1.3.6 (January 2017)
Minor Release Revision
* Core
  o Fixed a bad DLL issue where Google Drive was reporting a virus in the installer.
    Was an old version of the DLL. Replaced with up to date version.

1.3.5 (January 2017)
Minor Release Revision
* Core
  o Added Silent Registration

1.3.4 (January 2017)
Minor Release Revision
* Core
  o Minor About box code change
* Code Editor
  o Fixed Settings dialog not using white parent background
  o Added a Palette Parser to output palette data table
* Image Editor
  o Minor UDG panel change
  o Added ZX Spectrum Next palette support

1.3.3 (November 2016)
Minor Release Revision
* Image Editor
  o Added a ZX Spectrum Hi Colour palette (aka. Timex Hi Color Mode 8x1)
    Use the Palette Based Image parser to output graphics data
  o Added HiColour test project

1.3.2 (July 2016)
Minor Release Revision
* Core
  o Changed main toolbar play button icon to be the same as the Code Editor play icon
  o Reformatted About Box
  o Fixed incorrect hint in About Box
* Code Editor
  o Changed the replay/time lapse buttons to green

1.3.1 (July 2016)
Minor Release Revision
* Installer
  o Added missing cc3280mt.dll to Pasmo folder
* Core
  o Adjusted labels on About box
* Code Editor
  o Fixed bug with adding a new file to a new project
  o Fixed Snapshots memory leak
  o Fixed the Debug (Run, Pause, Stop) buttons
  o Fixed Timelapse/replay buttons
  o Fixed OSB view buffer indexing issue
  o Fixed Step-Over function
  o Made c, nc, nz, pe highlight as registers to fix silly syntax highlighting

1.3 (July 2016)
Major Release Revision
* Scorpio Components
  o Fixed an issue with data entry into spin edit controls
* Installer
  o Added Install as Admin
  o Added Big Sprites Demo project
  o Added the "Library\debugstring.asm"
* Project
  o Added all source to my local Git server (no not GitHub)
  o Added missing code references
  o Developing on Windows 10 to help with finding bugs
  o Fixed project file reference errors
  o Fixed incremental linking issue with C++ Builder 2007 on Windows 10
  o Fixed all project files to have the same version information
  o Re-Added (missing) Boriel ZX Basic demo with all the example files
    Also added a %Ask% dialog so you can choose the demo to run
* Core
  o Changed the toolbar to a white background
  o Changed all clWindows to clWhite
  o Changed all clBtnFace to clWhite
  o Fixed the tool button rendering
  o Fixed the display of project name in the title
  o Fixed the missing icon for the application
  o Added Pasmo to about box
  o Added Portable Z80 emulator to about box
* Code Editor
  o Added internal Emulator (Portable Z80 emulator)
    Uses Z80 core only
	All ZX Spectrum functions added by myself
  o Added Display View
  o Added Off Screen Buffer View
    Can display multiple buffers at a time
  o Added internal Debugger
    Added support for .map files
    Added support for .dbg files
    Added functions
      Hard Reset
      Run
      Pause 
      Stop
      Step Over
      Step In
      Step Out
      Trace
  o Added Replay 
    You can go back and forth in time, up to 5 minutes.
	If you go over 5 minutes; then you keep the last 5 minutes of play.
    Snapshot Rewind
	Snapshot Forward
	Single frame stepping with
	  Alt+Left  - back 1 frame
	  Alt+Right - forward 1 frame
  o Added Breakpoints
      Supports Pass Counts
      Persisted to project file
  o Added Debug string support
    Uses rst 0 redirection
	Need to:
	  Add "debugstring.asm" from Libary to your project. It will get copied
	  Include "debugstring.asm" in your source files.
  o Added Assembler (pasmo)
    Added support for .dbg files
    Added support for .sna files
  o Added Bookmarks
    Not persisted to project file
    Not persisted if file is closed in editor and then reopened
  o Added new toolbar for debug tools, display windows
  o Fixed Goto Line dialog
  o Fixed Build chain system (AGAIN!)
  o Common Tabs
    Added Breakpoint list
      Delete, Delete All, Enable/Disable (checkbox), Enable All, Disable All, Properties
    Added custom tab drawing
    Move tabs to bottom
    Made all font sizes the same in all tabs
  o Added %ask% as a substitution variable; so you can choose a target file for a builder.
* Image Editor
  o Fixed the different font size on all image type tabs
  o Changed everything to white background
  o Added a bar at the top of the active tab
* Map Editor
  o Changed everything to white background 
  o Added a bar at the top of the active tab

1.2.1 (April 2016)
Minor Release Revision
* Core
  o Removed the big Play button
    Looked ugly
  o Added a small normal tool button (F9 still works)
  o All dialogs now have white backgrounds (not windows gray)
* Code Editor
  o Added an Editor settings page to Settings dialog
  o Improved support for finding only monospace fonts (Damn you Consolas)

1.2.0 (April 2016)
Major Release Revision
Spit and Polish release
  Probably more spit than polish ;-)
  Nicer splash, better brand colours/icons/images/fonts, bigger toolbar buttons, tabs and some fonts.
  Better support for modern OS's (Windows 8+)
  Future versions will all be ZX Spectrum ONLY!
  NO MORE MULTI-MACHINE SUPPORT
* Installer
  o Moved all projects to the My Documents\TommyGun\ folder
  o Installer will only overwrite the example projects if the new files are newer
    If you make changes to the examples files you could lose those changes
    Clone the project and make changes to that copy
* Projects
  o Convert all projects to the new Build system
  o Set all emulators to ZX Spin 0.7s; as it is more reliable on Win7/8/10 than ZX Spin 0.666
  o Added a Boriel ZX Basic demo with all the example files
  o SabreWulf (fixed again)
  o Moved all projects to the My Documents\TommyGun\ folder
* Core
  o Added a RUN button to the main page
    Can use F9 to run
  o Moved the Log files to %APPDATA%\TommyGun
  o Fixed some log file handling
  o Updated the Splash screen
  o Updated the About box
    Updated the Titlebar image
    Removed AGD reference
    Removed SynEdit reference
    Added Scintilla reference
    Removed Easter Eggs
  o Fixed the Open a project form buttons
  o Added group boxes to project screen
  o Increased the size of all main plugin titles and their buttons
  o Increased the size of ALL toolbar buttons for bigger screens (bye year 2000; hello 2016)
  o Added stencil font used by application to installer
  o Fixed writing exception log to %APPDATA%
* Code Editor
  o Handle new event to update/build/run game
  o Replaced the Old SynEdit code editor with Scintilla
    Always hated the Borland style SynEdit editor
    Scintilla has a much more Visual Studio feel to it
    Scintilla DLL is also smaller than SynEdit (1646Kb to 432kb)
  o Fixed the Find/Search/Replace functions
    Consolidated search project files/find into a single dialog
    Simplified find/replace
  o Removed the editor options
  o Added addition Boriel ZX Basic keywords to the syntax highlighter in the Code Editor
  o Removed the Tools Save button. All operations save the Tool definitions
  o Added Default parameter definition to Tool definition
  o Added Accepts Multiple Input Files to Tool definition
  o Added Accepts Multiple Input Files support to the build pipeline
  o You can now use %pfolder% in a Tools executable path. Probably only effective for project batch build file stored in the project file.
  o Added the Boriel ZX Basic Compiler as a build tool
  o If you make changes to a build tool and change to a new tool; you are asked if you want to save the changes
    Because I always forget to click update
  o Fixed an issue where the installer would make the projects folders read-only and it wouldn't build the project
  o Fixed a Z80 lexer issue
* Image Editor
  o Fixed up the UDG editor to be similar to the character editor changes
    Easier to select a character
    Added magnification

1.1.0 (April 2016)
Major Release Revision
* Installer
  o Fixed installer to remove of TommyGun files after uninstall
  o New installs won't overwrite your Tools.xml settings file
* Projects
  o Added more projects to try
    SabreWulf (fixed)
    Space Invaders (90% complete)
    Gems (90% complete)
    Noughts and Crosses (from the Getting Started Guide)
    Buddy (a hacky demo)
    Z88DK - a working Z88DK "Hello world" demo
        see main.c for ZCC setup parameters
* Core
  o Changed the Machine name to show the project folder path
  o Removed the Tips dialog
  o Enter key works in the project list to load a project
* AGD Game Editor
  o Removed AGD Arcade Games Designer 
    There is a dedicated AGD editor in development
* Code Editor
  o Changed the Build system to use a "Tools" system
    Each tool has to be defined
    Each project specifies the tools it uses
    If a tool is not setup; then it is added and the user needs to define the location of the tool
    A tool is any application that is used outside of TommyGun
        e.g. Pasmo to compile assembly, Z88DK ZCC to compile C code, ZX Spin to run the project output
    You define whether a tool is a Builder or an Emulator
        Builders are used to compile the code
        Emulators are used to run the code
    The new Tools system will convert the old settings over the new system
    Once you have setup your tools; you shouldn't have to change them
  o Fixed a really annoying bug with the Build button where it would build every ASM file and not just the one in the emulator parameters
    You can supply any number of file names or use a wildcard (*.asm, *.c etc)
    And now not needed because I rewrote the build system
  o Removed the Build Selected and Stop buttons (I never use them, not sure they even work)
  o Added an Editor Options toolbar button. I wonder how long that has been missing?
  o Play button now does it all; Saves, Updates Resources, Builds and Runs the game (simples)
  o Fixed load compiler/emulator settings issue
  o Fixed issue where double clicking to goto an error line open a non existent file. If there was not a valid file on the line.
  o Fixed issue with Parameter substitution.
    Can now use %game% to get the game project name.
    For example: %game%.tap %game%.map to produce "My Game.tap" and "My Game.map" from pasmo.
  o Added bigger switch buttons to the Editor/Build Options dialogs
  o Fixed some keyboard handling issues
  o Fixed an issue where the application would crash while opening another project when files were opened in the code editor
  o Removed %infile% build variable
  o Updated %PFolder% and %game% build variables to work better
* Image Editor
  o Improved the Font selection panel
    Fixed all the control alignment issues
    Made it easier to select a character
    Shows the selected character in the preview window

1.0.0
Full version release
Only for ZX Spectrum and only for Arcade Games Designer
* Core
  o Added Scorpio logo
  o Updated splash/about box to include mention of Arcade Game Designer
  o Changed some UI colors
  o Hack for application not exiting correctly
* Arcade Game Designer
  o Added the Game Designer for AGD
  o Added the AGD compiler to the installation (TommyGun\AGD)
  o Added the AGD game engine ASM file
  o Fixed game editor property editor not updating correctly
  o Fixed score panel for AGD window
  o Added Sound Effect file selection
  o Added Diamond Geezer example game
  o Added support for user defined character set
* Code Editor
  o Added support for Game Designer (*.agd) files
  o Added the AGD code parser to build the resources into the AGD game engine
  o Added syntax highlighting for AGD files
  o Fixed some resource insertion bugs
  o Changed code editor search dialog to tabs (from tab buttons)
  o Fixed a rebuild project issue
  o Fixed issue with AGD and loading generated .asm files
* Map Editor
  o Added AGD mode, where you can assign the player, sprites and objects to screens
  o Fixed the display of the ScorePanel
  o Fixed Map editor showing all frames for sprites
  o Fixed use of score panel
  o Added ability to set a start screen
* Image Editor
  o AGD mode where you can't resize the image types for AGD or change the palette
  o Score panels are now screens and not tiles
  o Fixed tile/sprite/screen editor panels
  o Added magnification of tiles in the tile preview window
  o Added Character set type

0.9.42
Major Release Revision
* Application
  o Changed from Borland Builder C++ 6.0 to CodeGear C++ Builder 2007
  o Removed old FlatStyle components
  o Converted all controls over to XP/Vista themes
    Realigned a lot of controls and forms
  o Fixed some Scorpio VCL components (my components)
    Removed the old 3DStudioMax slim line scroll box
    All Scrollboxes are proper Windows scroll boxes
* MSX Tables Editor (NEW MAIN PLUGIN)
  o Adandoned!
* Added new computer support
  o MSX 1
  o TI-99/4a
  o NOT the colecovision (NEVER!!!)

0.9.40,41 (???)
Lost computer HDD and lost these revisions

0.9.39 (17 May 2009)
Minor Release Revision
* Code Editor
  o Fixed a bug with detecting error info to obtain program and line nos.
    ZX Basic: Error tag: 'Error', Program tag: '', Line tag: ''

0.9.38 (21 February 2009)
Release Revision
* Image Editor
  o Added support for new machine - Timex 20xx
* Code Editor
  o Added support for Tile Indexed map exporter (Timex 20xx/Spectrum SE)
  o Fixed a Monochrome (Palette Based Image parser) bug when exporting masked sprites/tiles.
  o Started new Map exporter - but sadly its incomplete
* Core
  o Added raw map data importer (Timex 20xx/Spectrum SE)

0.9.37 (18 January 2009)
Happy New Year
Release Revision
* Paletted Images Parser (CPC, Ent64 etc)
  o Fixed masking interlace bug - finally

0.9.36 (18 December 2008)
Release Revision
* SevenuP Parser
  o Fixed C source code formatting errors
* Code Editor
  o Added support for running batch files as "compilers"
* Paletted Images Parser (CPC, Ent64 etc)
  o Fixed masking interlace bug

0.9.35 (16 November 2008)
Release Revision
* Code Editor
  o Fixed a masking bug in the ImageLibrary.dll
  o Fixed a similar masking issue in the Paletted Images Parser

0.9.34 (1 November 2008)
Release Revision
* Code Editor
  o Fixed a resource selection bug
* Map Editor
  o Added support for using sprites as animated tiles
* Map Parser
  o Rearranged the parser options
  o Added support for merging sprites as animated tiles
  o Added an option to format the tiles table

0.9.33 (24 October 2008)
Release Revision
* Code Editor
  o Fixed a bug in the selection and updating of the files list
  o Changed the Add Resource parser combo box to a list box (easier to find parsers)
  o Map Parser
    . Fixed a screen name bug
    . Added a Post Process step to allow for compressors to run on the map data
    . Added a Map Table sort order (Screens may still be stored out of order)

0.9.32 (7 July 2008)
Major Release Revision
* Example Projects
  o Updated the Space Invaders project
    . Includes the latest code and graphics
  o Added the GEMS project
    . Includes all images, music and source code to date
* Core
  o Removed the PayPal donation button on the About Box
    . Its invisible to most people so no big lost there!
  o Reformatted all editor plugins to have the titles at the top and the toolbars below.
  o Adjusted some of the TommyGun colours
  
  !!!TRY HIDING THE MAIN TOOLBAR AND SHOWING THE CHOOSER - NICE!!! ;-)

* Music Editor
  o Changed UI to a proper Music editor style
    . Bpm settings
    . Patterns (collection of notes - can be multi-channel)
    . Channels (can restrict the number of channels for a pattern)
* Code Editor
  o Hid the uncompleted Code Browser tool buttons
  o Added a Close active document to the window buttons
  o Added support for BASIC compilers - *.bas files
    . Added a BASIC highlighter
  o Added a Find In Files feature
  o Fixed bug in Palette Based Image Parser to do with Number Base
  o Vic20 parser
    . Fixed Double Height code generation issues
* Image Editor
  o Palette Base Images Parser
    . Changed the default source code selection to ASM
    . Fixed a code generator bug with ',' in arrays
    . Comments are generated by the file extension
      - .c, .cpp, .h and .hpp all use C style comment /* */
      - anything else use Asm comments ;
  o Fixed width for Sprite/Tile image types
    . Minimum width is the smallest number of pixels per byte.
  o VIC20 MultiColor palettes
    . Fixed the setting of pixels
* Map Editor
  o Fixed variable sized pixel bitmaps (aka "Fat" Pixel modes - eg. Vic20, CPC)

0.9.31 (17 June 2008)
Release Revision
* Image Editor
  o Made 4x4 the minimum image size for Fonts, Tiles and Sprites
  o Fixed Vic20 character index output for code editor data parser
  o Updated Palette Based Images data parser
    . Added C output support
    . Added size output ordering
    . Added a byte definition value eg. you can use .db DEFB DB .byte etc    
* Code Editor
  o Made the Code generator tags to be assembler and C friendly
  o Palette based parser (CPC, Ent64, C64 etc)
    . Added C Source output

0.9.30 (1 June 2008)
Release Revision
* Image Editor
  o Fixed Vic 20 palettes
  o Changed default screen size to 160x192 from 176x184
  o Fixed mask generation for all palettes
* Code Editor
  o Added a Vic20 specific code parser
  o Updated the SevenuP (Z88DK) parser
    . Includes Label Prefix and Postfix definitions
  o Added a splitter so you can resize the dialog components
  o Palette based parser (CPC, Ent64, C64 etc)
    . Includes Label Prefix and Postfix definitions
    . Fixed the mask generation values for interleaved values (CPC)

0.9.29 (30 April 2008)
Release Revision
* Image Editor
  o Fixed an image list removal bug
  o Change Vic-20 MultiColor palette design/behaviour
  o Added Vic-20 Double Height palettes for MultiColor and HiRes

0.9.28 (20 April 2008)
Release Revision
* Image Editor
  o Added VIC-20 Hires palette
  o Added VIC-20 MultiColour palette
  o Fixed up general Vista issues and palette forms
* Core
  o Made it easier to find the About Box EASTER eggs.
    . ie. Move the cursor over the red box, the silver fern and the KiwiWare text
* Code Editor
  o Added VIC-20 support to the Palette Based Images code parser/generator
  o Fixed a bug in the File List when adding files and moving items around
* Installer
  o Organised the installer Machine order to be Alphabetical

0.9.27 (5 April 2008)
Release Revision
* Updated SynEdit component to 2.0.6
* SevenuP Code Parser
  o Can now parse Monochrome images
* Image Editor
  o Fixed the FloodFill tool
* Maps Parser
  o Added support for Index only tile maps (no co-ordinates)
    . A screen should have a tile at all positions in the map
    . If a tile is missing from a position then tile 0 is used
    . All tiles must be the same size
* Map Editor:
  o Added an Overwrite tile option
  o Also now save the grid size option to the map file so set this if you use Tile index only maps
* Code Editor:
  o Added Copy to clipboard to the Console output window
  o Added new rules for jumping to output errors.
    1. If no 'error prefix' is set then only a line no. and file need to be present
    2. If 'error prefix' is set then error, line no and file must be present on the line
    3. No 'file prefix' means to just search for the first '.' to find a file from there
    4. If a 'file prefix' is set then the search for a file starts from that position on
  o The exit code is now retrieved from the output of the compiler 
    An appropriate message is displayed on success or failure
* Tutorials
  o Fixed the SabreWulf project to compile again (use Pasmo)
* Installation Files
  o Removed the TommyGun Conversion Utility
    As I'm sure no would need it by now.

0.9.26 (19 February 2008)
Patch Revision
* SevenuP Code Parser
  o Fixed number base examples

0.9.25 (19 February 2008)
Patch Release
* SevenuP Code Parser
  o Fixed a problem with the output of Attributes and Attribute Masks (Again ;-) )

0.9.24 (18 February 2008)
Patch Release
* SevenuP Code Parser
  o Fixed a problem with the output of Attributes and Attribute Masks

0.9.23 (14 February 2008)
Patch Release
* Image Library
  o Fixed a problem with the dirtiness of image rects
    Most obvious when creating 8x8 Sprites    

0.9.22 (1st October 2007-14 February 2008)
Release Revision
* Code Editor
  o Fixed bug in Spectrum Image parser when using masks
  o Fixed bug in the Text drawing tool.
  o Added a SevenuP parser for Z88DK and SP1 support
    No Interleave option: Defaults to Sprite

0.9.21 (14th June 2007)
Release Revision
* Map Editor:
  o Finally implemented the new tile drawing tools
    Should help to make drawing levels easier
    Free          - place tiles anyway
    Line          - Draw tiles in a line
    Rect          - Draw an unfilled rectangle of tiles
    Filled Rect   - Draw a filled rectangle of tiles
    Circle        - Draw an unfilled circle of tiles
    Filled Circle - Draw filled circle of tiles
  o Sped up moving of large selection of tiles
* Image Editor:
  o Added an Import Image Sheet dialog (under File|Import)
    Allows you to import tiles or sprites from within a large image sheet
    with many scattered images in it.
  o Fixed image resizing to also resize the mask of all frames
  o Fixed image resizing to allow resizing while the mask mode is on
  o Fixed the Generate Mask tool to generate masks for all frames of an image
  o Fixed a bug in creating masks when the image width is not a multiple of 8
  o Added a Set Hot Spot marker (and a toggle button to show/hide it)
    WTF is a Hot Spot? Well best off not to be using it then eh! :)
  o Fixed a bug where the Animation Frame Helper would freeze on Frame 0

0.9.20 (4th June 2007)
Release Revision
* Demo Projects
  o Fixed the SabreWulf demo to build correctly
  o Fixed the Noughts and Crosses demo to build correctly

0.9.19 (17th March 2007)
Release Revision
* Core:
  o More DPI issue fixes
  o Fixed Window restore when starting up in maximized window mode
* Image Editor:
  o Fixed magnification problem (from Font issue)
  * Fonts Plugin
    o Fixed font names list
* Map Editor:
  o Fixed the Score Panel div by zero bug

0.9.18 (3rd March 2007)
Release Revision (EP64/128)
* Code Editor:
  o Fixed Sam Coupe Mode 3 & 4 parser output
* Image Editor
  o Fixed SpectrumNext256 64/128 16/Attribute palettes
  o Fixed images limited to 512 pixels wide.
  o Limited magnification of images to 2048x2048 pixels
    (due to memory and Win32 resource limitations)
  o Fixed bug with Fill draw tool (temporary fix)
* Core:
  o Fixed DPI issues within main plugin area

0.9.17 (20 February 2007)
Release Revision
* Machines
  o Added new machine - SpectrumNext256 64/128
* Map Editor:
  o Fixed a Home/End key conflict with the code editor
  o Fixed some settings components
  o Moved tool buttons onto different toolbars
  o Fixed the 16 colour map window bug
* Code Editor:
  o Added C and CPP comments as valid comments for Z80 Assembler.
  o Fixed F3 jumping bug
  o Fixed Spectrum Image Parser always producing attributes
  o Changed Spectrum Image Parser to be a generic Attribute parser
    - works for ZX Spectrum, Sam Coupe, SpectrumNext256 64 etc
* Image Editor
  o Added SpectrumNext256 64/128 - 2/4/16/256 colour palettes
  o Fixed Sam Coupe Mode palettes
    - fixed incorrect colour orientation (Mode 3&4)
    - fixed incorrect attribute information (Mode 2)
  o Added Machine logos to all colour palettes
  o New improved color selection dialogs

0.9.16 (23 December 2006)
Release Revision
* Image Editor:
  o Added selection move and clone
    - Hold ctrl to clone(copy) the selection and move it
    - Hold shift to snap the mvements to the grid (as per usual)
  o Added an Arbitary Rotate
    - New button on the image tools toolbar (has red dots)
    - Can rotate an image to ANY angle from ANY centre point WITHIN the image
    - CANNOT rotate selection at the moment only the whole image
    - and as per all the other rotate/mirror/flip function it only operates on the current frame 
* Map Editor:
  o Fixed the tile selection indicator bug
  o Fixed a bug with restoring/saving tile backgrounds
* Code Editor:
  o Added a Clear Console options to the build options

0.9.15 (13 December 2006)
Release Revision
* Code Editor:
  o Fixed Build and Run shortcut keys
    Ctrl+F9 to compile
    F9 to run (will compile project if its changed)
* Map Editor:
  o Added Map menu
  o Added Save Map as Bitmap (in Map menu)
    Saves the map at the current scale
  o Add Multiple selection
    Changed the way add tiles works (ever so slightly)
    - Do rectangle select by selecting an empty area first then click and drag
    - Can add to selection with Ctrl - sorry no removal at the moment
    - click a blank area to clear the selection
  o Fixed Undo/Redo of screen selection
    - updated undo/redo to work with multiple selection
  o Added Screen swap in screen editor (lower window)
    - Hold Shift while dragging a screen and drop it on the screen you wish to swap with
  o Added Clone Tile selection
    - Select tiles
    - Hold Ctrl while click on a selected tile and moving/dragging it will clone the selection
  o Added Copy/Cut and Paste of tiles
    - Can paste to other screens
* Core:
  o Added a copy project feature
    You can use projects as base projects or project templates
    Thanks to Skarpo on WoS for the tip

0.9.14 (1 Nov 2006)
Release Revision
* Image Import:
  o Added support for creating images with a mask
* Image Editor:
  o Fixed a problem with Masked mode
  o Added Generate Mask functionality
  o Added a Show Previous Frame Underlay toolbar button (toggle animation helper)
    This should help when doing animation so you can compare one frame
    to the next (or current frame)
    The underlay uses the mask colour and transparency values, so
    you can use the transparency slider to fade between the current frame
    and the previous frame
* Strings Editor:
  o Added the new string table editor
  o Also a new parser for the strings (see CodeEditor)
* Code Editor:
  o Added a string table parser

0.9.13 (13th Oct 2006)
Superstition Release
* Skipped because I don't like the number 13. ;-)
  Plus its black friday.

0.9.12 (12th Oct 2006)
Release Revision
* Code Editor:
  o Fixed a DEL key bug in the project files list
* Map Editor:
  o Fixed a transparency bug
* Image Importer:
  o Fixed a SevenuP image import bug

0.9.11 (1st Oct 2006)
Release Revision
* Machines:
  o Added initial support for Jupiter Ace and Jupiter Ace 4000
    - Added palette plugin
    - Added code parser
    - Added UDG support
* Code Editor:
  o Added editor properties dialog
    - can customise the text editor
      Colour schemes
      Key mappings
      Display properties
      and General Editor properties
  o Moved the build settings to a new dialog box
  o Added the Jupiter Ace Chunky graphics parser
  o Updated to version 2.0.3 of SynEdit
  o Added ZigZag support to ZX Spectrum image parser
  o Added Mask BEFORE or AFTER for mask pixel pairs to ZX Spectrum image parser
  o Added ability to remove Attributes from ZX Spectrum image parser
  o Fixed C64 palette drawing bug
* Image Editor:
  o Added the Jupiter Ace Chunky graphics palette
  o Fixed copy/cut/paste bug
  o Fixed image tools bug
  o Added image resizing
    Only Sprites and Tiles are resizeable
  o Images can now be any width and any height
    WARNING!!!Be aware that non byte aligned values could act strangely!!!
  o Added an Invert Mask button
  o Fixed Mask mode button (to apply to all frames of an image)
* Map Editor:
  o Tiles are by default transparent
  o Supports Masked Tiles

0.9.10 (7th Sept 2006)
Release Revision
* Projects:
  o Fixed SabreWulf project

0.9.9 (6th Sept 2006)
Release Revision
* Code Editor:
  o Yet more changes to the Amstrad CPC code parser
    Hopefully working completely
* Image Editor:
  o Again changes to the Amstrad CPC palettes
    Hopefully fixed for good!
* Core:
  o Added TommyGun website link to About box

0.9.8 (5th Sept 2006)
Release Revision
* Image Editor:
  o Fixed major bug in all palette plugins
    All 1.0 projects will be automagically fixed once loaded and 
    saved in the correct format once save is clicked.
    New project version is now 2.0 up from 1.0
* Code Editor:
  o Fixed all the parsers to use the new correct palette formats
  o Pretty sure the CPC parser is now 100% correct
  o Added Pixel Row Order to palette based parser
    You can order pixel rows classically ie. left to right stacked
    Or Zig Zagged in left to right then right to left alternating rows
* Scorpio VCL Components:
  o Fixed problem with XML files and double quotes

0.9.7 (27th Aug 2006)
Release Revision
* Image Editor:
  o Tiles can now be masked
* Code Editor:
  o Added more options to the Paletted based Image Parser
    This is to support interlaced byte formats for palette indexes
    e.g. Amstrad CPC.
    Sorry - Custom bit remapping is incomplete at present
  o Added a Number base option to image parsers to output numbers in any base.
  o Added a new ZX Spectrum SCREEN$ parser

0.9.6 (25th July 2006)
Release Revision
* Code Editor:
  o Fixed the palette image parser
    Now parsers the Amstrad CPC palettes correctly.
    Should now work for Monochrome and C64 as well.

0.9.5 (12th July 2006)
Release Revision
* Minor fixes

0.9.4
Release Revision
* Code Editor:
  o Fixed copy/cut/paste problem in edit boxes in the settings tab
  o Fixed tab order in settings

0.9.3
Release Revision
* Main Framework:
  o Added a new Backup and Restore feature
    It can be configured from the options dialog
    It also adds an extra button on the Start up page, that allows you to
    choose a project to restore.
    You cannot currently restore Deleted projects, this has to be manually at present.
  o Made all the Options icons have a blue theme :-)
  o Minor re-styling of the options page layouts
  o Removed the old problems dialog - not needed for new xml files
  o Updated to some WinXP menu icons
  o Fixed Window size and position restore (well for a single monitor system anyway)
  o May of fixed the sticky dirty flag bug (maybe!)
  o Updated the About box to include Copyright information.
  o Fixed some start screen component colours
* Code Editor:
  o Fixed a couple of problems with the Load File button
    Now correctly copies any files not in the project folder into the project folder
    Also renames any files that have spaces to use underscores
    Makes jumping to error statements after a compile easier :-)
  o Paletted based image parser. 
    Fixed handling of masks.
    Changed default endianess to Big endian (Z80)
  o Fixed a problem with the code editor creating a blank tab
  o Fixed a GotoLine bug when no file was being edited
  o Removed the main menu icon for GotoLine as it was the wrong one
  o Improved the Build and Run commands with respect to dirty files
  o Change title from "Text Editor" to "Code Editor"
* Image Editor:
  o Font Editor
    Fixed a problem with the font naming of each character
    Will fix old fonts automagically as they are loaded
    Fixed the character button hints 

0.9.2
Release Revision
* Image Importer:
  o Changed all import modules to use ifstream instead of fopen/fread
  o Fixed the reading of the mask values from a SevenuP file
* Code Editor:
  o Implemented the update resources before building option
  o Implemented the save files before building option
  o Implemented Jump to error if build fails
  o Implemented build project if dirty before running
  o Changed Run shortcut from F5 to F9 to match Borland compile and run shortcuts
  o Added Build Presets option to allow easier 
    access to preset build environment variables
  o Added a new command line variable %game% to help 
    supply default command line parameters.
  o Updated the Update resources button so now you don't need to have a
    file loaded for its resources to be reparsed.
* Image Editor:
  o Fixed masked images not added new frames correctly
  o Fixed bug where mask mode wasn't honoured when a new frame was created or cloned

0.9.1
Release Revision
* Image Editor:
  o Added mouse wheel zoom in/out for an image
  o Fixed a problem with the grid toolbar buttons
  o Fixed an annoying copy/cut/paste bug in the image editor
* Code Editor:
  o Fixed incorrect cursor position information on status bar

0.9.0
Minor Release Revision
* Internal revision change over

0.8.9
Release Revision
* Main Framework:
  o Fixed how the short-cut keys are shared between plugins
  o Added the Terminate button to the Exception dialog
* Image Editor:
  o Fixed the selection cursor hot spot
  o Fixed delete to remove the selection of an image
    But only when NOT in an editable Win32 control
  o Fixed copy/cut/paste selection problem
    Selection rect reset to full image size once c/c/p is complete
  o Can create tiles of any height if the palette supports it
  o Fixed the Exceptions Dialog - added the terminate button
  o Fixed CPC modes
    Mode 1 uses square pixels
    Mode 0 uses fat    pixels
    Mode 2 used thin   pixels
  o Fixed Line Drawing Tool
  o Fixed Sprite and Tile image viewers
  o Added a key panel to the options panel - to show the Shortcut keys
* Map Editor:
  o Fixed problem with the Tile browser not updating when new tiles are created
  o Implemented ShortCut keys
  o Added Shortcuts keys panel to the options
* Code Editor:
  o Added a key panel to the options panel - to show the Shortcut keys

0.8.8
Release Revision
* Image Editor:
  o Fixed a divide by zero error in the new Custom Mode Scale Adjust feature
  o Fixed bug with Centering image on and auto mag off, 
    and not showing all of image correctly
* Code Editor:
  o Fixed Rename option so it renames the file tab if the file is open

0.8.7
Release Revision
* Image Editor:
  o Improved palette importing of bitmaps
  o Added a Mode Scale Adjust options to the settings
    This allows a 1x1 pixel view of "fat" hardware modes on certain machines such as,
        Amstrad CPC Modes 0 & 1
        Commodore C64 hi-res mode
        Sam Coupe Modes 3 & 4

0.8.6
Release Revision
* Fixed donations button to point to the correct email location
* Image Editor:
  o Completed the UDG image type
  o Completed the Font image type
  o Fixed palette bug in ZX Spectrum, Monochrome, Sam Coupe Modes 1 & 2
* Code Editor:
  o Fixed a bug with multi-file tabs
  o Fixed a bug with the removal of files
  o Fixed a bug with MoveUp and MoveDown button for project list
* Installer
  o Placed the Music Composer and the Memory Map editor into an Experimentals Section
  o Customized the Installer a little
  o Added a TommyGun.tips file - still need to add new tips to it

0.8.5
Release Revision
* Added a Getting Started Guide
  Guides you through the process of running the SabreWulf project and
  also on how to create a working game.
* Bug fixes
      o All palettes except the ZX Spectrum and Sam Mode 1 can have any height of sprite or tile
        All images still MUST have a width that is a multiple of 8!
        This limitation will be removed later
      o Fixed a placement problem with certain dialogs (including some palette dialogs)
      o Fixed sprite list item selection problem
* Main Framework:
    o Added project delete button to the startup screen when hovering over a project entry
    o Updated Undo/Redo
        o Supported by Image Editor and Map Editor only
          o Code Editor is a 3rd party tool that requires much work to integrate 
            into my Undo/Redo system, so Undo/Redo buttons disabled while in Code Editor
          o Added many configuration options for Undo/Redo
* Map Editor: 
    o Added Zoom factor for tile browser
    o Fixed the selection tool from jumping to the origin of an object
    o Fixed the score panel (I think)
* Image Editor: 
    o Palette updates
      o The screen editor now includes all default screen sizes for each screen mode
    o Palettes show wide pixels for mode where it is required eg. CPC Mode 1, 2
      o Fixed masking of other palette types (besides the ZX Spectrum)
      o Updated all palettes to be able to convert bitmaps formats
          (enables the palette to support copy/cut/paste and image tools)
    o Implemented Image Shift/Rotate/Mirror and Flip operations
    o fixed some Settings controls
    o Implemented Copy/Cut and Paste for Image Editor
      o Added Undo/Redo for Cut, Paste and the Image tools (shift/scroll, rotate, mirror, flip)
      o Supports pasting images from an outside source
    o Supports copying/cutting the bitmap to the clipboard
    o Added Selection tool cursor in the Image Editor
* Code Editor: 
    o Added tabbed multi-file support
    o Added goto error line in the console window (double click, or right click popup menu)
    o Added save console window to file
    o Improved syntax highlighting for Z80 assembler
    o Added syntax highlighting for C/C++
    o Added normal text mode highlighter (ie. no highlighting) 
    o Fixed the find text dialog
    o Find and Replace dialogs get the current text selection or word at cursor now
    o Implemented the file statistic panel
* Music Composer:
    o Added the beginning of a Music Composer (similar to BASin's Beep composer)
      !!!WORK IN PROGRESS!!!
* Memory Layout:
    o Started on a memory layout editor
      Requires memory.xml file in each machine folder to be defined
      Only supports the 48K Spectrum at present
      Will be able to read .maps files to fill in blocks of memory
      !!!WORK IN PROGRESS!!!

0.8.4
Release Revision
* SAM Palettes for Modes 1 - 4
  1 & 2 - Has fixed ZX Spectrum colours 
        These are not defineable from the std 128 colour palette
  3 & 4 - User can define the colours from the std 128 colour palette
* Completed Undo/Redo for the Image, Map and Code editors
* Finished Undo/Redo for ImageEditor
  Works on Creation, Deletion, Cloning, Rename, Selection

0.8.3
Release revision
* ZX Palette BUG FIX!
* Some other minor bug fixes.
* Added full Undo/Redo system (disabled in the Image editor until next release due to bug fixes)
* Added a Short-Cut Keys panel to the options page (again incomplete due to rushed bug fix release)

0.8.2
Release revision
* Fixed the CPC Mode 1 & 2 palettes to show the correct system default colours.
* Fixed the CPC and C64 palettes to save the user configured colours for a project.
* Added the Sam Coupe Mode 0 and Mode 1 palettes

0.8.1
Release revision
* Added the C64 and Amstrad CPC colour image palettes.
  Includes masking ability
* Also added the Palette Image Parser for the C64 and CPC and similar palette based machines.
* Updated the source code to the SabreWulf project.
* Enabled the outputting of mask data in the ZX Image parser
* Made the Image Editor grid colours configurable.

0.8.0 and earlier
Major revisions
* HEAPS OF STUFF




Legal stuff.
============
TommyGun is freeware and is (c) copyright 2004-2016 Tony Thompson.
You cannot distribute TommyGun without my permission and without giving me credit.
And you MOST certainly cannot charge for TommyGun.
Anything you make with TommyGun is all yours of course.

I hope you enjoy using TommyGun!
