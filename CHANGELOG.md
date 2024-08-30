# CHANGELOG

## v0.9.0-alpha

### Added

* *.markdownlint.json*
* *.clang-format*

### Updated

* *src/main.cpp*
  * Updated version number
* *Makefile*
  * Updated version number
* *CHANGELOG.md*
  * Updated format
* *.gitignore*
  * `.markdownlint.json` files is no longer ignored
  * `.clang-format` files is no longer ignored
* *.clang-format*
  * Updated formatting

## v0.8.0-alpha

### Added

* *SECURITY.md*
* *src/res/img/bar/Time-0001.png*
* *src/res/img/bar/json/Time-0001.json*

### Updated

* *TODO.md*
  * Updated TODO list
* *include/equation_answer.h*
  * Changed type `int` to type `float`
* *Makefile*
  * Updated version number
  * Updated name of debug target
* *src/equation_answer.cpp*
  * Changed type `int` to type `float`
  * Return result is now a `float` instead of an `int`
* *src/main.cpp*
  * Updated version number
  * Added debug printf statements
  * Updated format

### Removed

* *TODO.md*

## v0.7.0-alpha

### Added

* *TODO.md*

### Updated

* *Makefile*
  * Updated version number
* *src/main.cpp*
  * Updated version number
  * No errors are now thrown when `inputedString` is empty
  * Commas can now be entered
* *include/equation_answer.h*
  * Updated format
* *src/equation_answer.cpp*
  * Updated format

## v0.6.0-alpha

### Added

* *TODO.md*

### Updated

* *Makefile*
  * Updated version number
  * Revamped makefile for consistency and simplicity
* *src/main.cpp*
  * Updated version number
  * Mistakes can now be corrected when entering numbers
  * Updated format
  * Optimized code
  * Negative numbers can now be entered

### Removed

* *docs/main-layout.png*
* *TODO.md*

## v0.5.0-alpha

### Added

* *TODO.md*
* *equation_answer.h*
* *equation_answer.cpp*

### Updated

* *Makefile*
  * Updated version number
  * Added the file "equation_answer.cpp"
* *include/equation_answer.h*
  * Updated format
* *src/equation_answer.cpp*
  * Updated format
* *src/generate_equation.cpp*
  * Updated variables
  * Updated random equation generation
  * Updated format
* *src/main.cpp*
  * Updated version number
  * Added implementation of the equation_answer.h library
  * Equations can now be answered
  * Updated format

### Removed

* *TODO.md*

## v0.4.1-alpha

### Added

* *src/res/img/character/teacher-0001.png*

### Updated

* *src/main.cpp*
  * Added teacher sprite
  * Moved teacher sprite

## v0.4.0-alpha

### Added

* *src/res/img/window/window-0001.png*
* *src/res/img/background/background-0001.png*

### Updated
  
* *.gitignore*
  * .aseprite and .ase files are now being ignored
* *Makefile*
  * Updated version number
* *src/main.cpp*
  * Updated version number
  * Added input window
  * Moved position of the equation font
  * Moved postition of the input font
  * Added background

### Removed

* *src/res/img/background/*
* *TODO.md*

## v0.3.1-alpha

### Added

* *docs/main-layout.png*

### Updated

* *Makefile.md*
  * Updated version number
* *src/main.cpp*
  * Updated version number
  * Update layout of fonts

## v0.3.0-alpha

### Added

* *TODO.md*
* *include/generate_equation.h*
* *src/generate_equation.cpp*

### Updated

* *Makefile*
  * Updated version number
  * Removed "-mwindows" argument from debug target
* *src/main.cpp*
  * Updated version number
  * Added implementation of generate_equation.h
  * Implementation of random equation being displayed on screen
* *README.md*
  * Updated version
* *docs/how_to_compile.md*
  * Corrected grammar and spelling

### Removed

* *TODO.md*

## v0.2.1-alpha

### Updated

* *CHANGELOG.md*
  * Updated format
* *src/main.cpp*
  * Removed unneccesary logging

## v0.2.0-alpha

### Added

* *TODO.md*

### Updated

* *TODO.md*
  * Updated TODO list
* *src/main.cpp*
  * Keyboard inputs are now displayed on the screen
  * All characters except numbers are now rejected
  * Numbers entered are now being merged into a single string
  * Removed an unnecessary function
  * Length and width of the rendered number-string are now automatically handled
  * Formatted code
* *Makefile*
  * Added logging
  * Added an argument to the debug target

## v0.1.16-alpha

### Added

* *TODO.md*
* *src/res/img/background/test-0001.png*

### Updated

* *Changelog*
  * Fixed formatting issue
* *src/res/img/background/test-0001.png*
  * Removed metadata
* *src/random.cpp*
  * Updated format
* *.gitignore*
  * Now ignoring .clang-format and tmp files
  * Now ignoring .ttf and .otf files
* *Makefile*
  * Updated version number
  * Added SDL_ttf library compilation
* *.vscode/settings.json*
  * Updated associations x2
* *docs/how_to_compile.md*
  * Updated instructions on how to compile
* *docs/naming_definitions.md*
  * Updated naming definitions
* *src/main.cpp*
  * Updated version number
  * Made resizing of textures possible
  * Set texture rendering mode to linear
  * Added key input system
  * Updated format x2
  * Made window fullscreen
  * Added font support

### Renamed

* *src/res/img/misc/background-0002.png*
  * Renamed to "src/res/img/misc/background-0001.png"

### Removed

* *src/res/img/misc/background-0001.png*
* *TODO.md*

## v0.1.15-alpha

### Added

* *TODO.md*
* *src/res/img/misc/background-0002.png*
  * Test background

### Updated

* *Makefile*
  * Added debug option
  * Updated format
* *TODO.md*
  * Updated status
* *src/main.cpp*
  * Added random operator logic
  * Made window full-screen

### Removed

* *TODO.md*
* *src/res/img/misc/background-0001.png*
  * Removed due to irrelevance

## v0.1.14-alpha

### Updated

* *.vscode/c_cpp_properties.json*
  * Intellisense now uses MYSYS2 MinGW Clang++
* *.vscode/settings.json*
  * Removed unneccesary fuction
* *src/main.cpp*
  * Changed main fuction to WinMain
* *.gitignore*
  * Now ignoring "bin/"
* *docs/how_to_compile.md*
  * Updated instructions on how to compile with MYSYS2 Clang++
* *Makefile*
  * Updated Makefile to compile with MYSYS2 Clang++
* *README.md*
  * Updated README

## v0.1.13-alpha

### Added

* *src/random.cpp*
* *include/random.h*
* *.vscode/settings.json*

### Updated

* *src/main.cpp*
  * Added test logic for random number generation
* *docs/how_to_compile.md*
  * Updated instructions on how to compile
* *.gitignore*
  * Directory "include" is now longer ignored
* *Makefile*
  * Now compiling with Windows librarys

## v0.1.12-alpha

### Updated

* *docs/c_cpp_properties.json*
  * Changed intelliSenseMode
* */*
  * Changed all line breaks from CRLF to LF
* *Makefile*
  * Updated version number
* *src/main.cpp*
  * Updated version number

## v0.1.11-alpha

### Updated

* *Makefile*
  * Added version variable
* *main.cpp*
  * Added version variable

## v0.1.10-alpha

### Updated

* *Makefile*
  * Added clean rule

## v0.1.9-alpha

### Added

* *src/res/sfx/music/test.ogg*

### Updated

* *docs/how_to_compile.md*
  * Updated instructions on how to compile with Makefile
* *CHANGELOG.md*
  * Completely revamped format
* *src/main.cpp*
  * Added ogg file playability
* *.gitignore*
  * .markdownlint.json is now ignored
  * TODO.md is now ignored

### Deleted

* *src/res/sfx/music/test.wav*
* *TODO.md*

## v0.1.8-alpha

### Updated

* *Makefile*
  * Completely revamped Makefile
* *main.cpp*
  * Fixed type

### Removed

* *.vscode/tasks.json*
* *.vscode/launch.json*

## v0.1.7-alpha

### Updated

* *CHANGELOG.md*
  * Updated format
* *docs/how_to_compile.md*
* *docs/naming_definitions.md*
* *src/main.cpp*
  * Added SDL-mixer
  * Refreshed comments
  * Added code for sound test with wav files
-*Makefile*
  * Slight modifications

## v0.1.6-alpha

### Updated

* *docs/how_to_compile.md*
* *LICENSE.md*
* *README.md*

## v0.1.5-alpha

### Added

* Lost source code
