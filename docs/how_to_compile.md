# How to compile

## Neccesities

### Windows

#### Compiler

First of all, you need to download MinGW. You can download the installer [here](https://github.com/msys2/msys2-installer/releases/download/2024-07-27/msys2-x86_64-20240727.exe).
Run the installer and let the program install. If it finished installing, run a
program titled "MYSYS2 MINGW64". Run the following commands:

```shell
pacman -Syu --noconfirm
pacman -Su
pacman -S mingw-w64-x86_64-clang --noconfirm
pacman -S mingw-w64-x86_64-gcc --noconfirm
pacman -S mingw-w64-x86_64-make --noconfirm
```

Now, after you finished installing Clang, GCC and Make, add your "bin" directory
to the system path. The bin directory is typically located at
"C:\msys64\mingw64\bin".

Restart your computer and verify your installation of Clang, GCC and Make by
typing these commands:

```shell
clang --version
gcc --version
mingw32-make --version
```

#### Librarys

This project requires the SDL2, SDL2_image and the SDL2_mixer library. First,
create a directory titled "lib" inside your project directory. Create another
directory inside the "include" directory of your project called "SDL2". Inside
your "lib" directory, create another directory titled "x64". The last step is
to create a directory called "bin" inside your root directory.

Now, download the SDL2 files from [here](https://github.com/libsdl-org/SDL/releases/download/release-2.30.6/SDL2-devel-2.30.6-mingw.tar.gz),
the SDL2_image files from [here](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-mingw.tar.gz),
the SDL2_mixer files from [here](https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-mingw.tar.gz)
and the SDL_ttf files from [here](https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-mingw.tar.gz)

Unpack all archives and run the following commands:

```shell
mv SDL2-2.30.6/x86_64-w64-mingw32/include/SDL2/* MathOrDeath/SDL2/include/
mv SDL2-2.30.6/x86_64-w64-mingw32/lib/* MathOrDeath/lib/
mv SDL2-2.30.6/x86_64-w64-mingw32/bin/* MathOrDeath/bin/
mv SDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2 MathOrDeath/SDL2/include/
mv SDL2_image-2.8.2/x86_64-w64-mingw32/lib/* MathOrDeath/lib/
mv SDL2_image-2.8.2/x86_64-w64-mingw32/bin/* MathOrDeath/bin/
mv SDL2_mixer-2.8.0/x86_64-w64-mingw32/include/SDL2/* MathOrDeath/SDL2/include/
mv SDL2_mixer-2.8.0/x86_64-w64-mingw32/lib/* MathOrDeath
mv SDL2_mixer-2.8.0/x86_64-w64-mingw32/bin/* MathOrDeath
mv SDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2/* MathOrDeath/SDL2/include/
mv SDL2_ttf-2.22.0/x86_64-w64-mingw32/bin/* MathOrDeath/SDL2/bin/
mv SDL2_ttf-2.22.0/x86_64-w64-mingw32/lib/* MathOrDeath/SDL2/lib/
```

Next, download the following fonts and put them in the "src/res/font"
directory:
> [Press Start 2P](https://fonts.google.com/specimen/Press+Start+2P)

Now, just navigate to your project root and execute this command

```shell
mingw32-make
```

The programm can now be executed.
