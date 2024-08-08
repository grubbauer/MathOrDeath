# How to compile

## Necessities

### Windows

- clang-cl Compiler
- SDL2
- SDL2-mixer

To compile the code, you will have to download the clang-cl compiler for Windows.
After downloading the compiler, you need to install it and add it to the Windows
Path Environment Variable.

After that, you need to create a directory inside the project folder titled
"include" and then inside the "include" directory, you will need to create another
directory titled "SDL2". Now, you will need to download the VC-SDL2 package from
[this](https://github.com/libsdl-org/SDL/releases/download/release-2.30.6/SDL2-devel-2.30.6-VC.zip)
link. Unzip the contents and move all files inside the "SDL2-x.xx.x/include"
directory of the zip file inside the "include/SDL2" you've created. After that,
create a new directory inside your workspace titled "lib" and again inside this
directory create another directory called "x64". Now copy all files inside the
"SDL2-x.xx.x/lib/x64/" of the zip file inside of the "lib/x64/" directory.

Now you need to download the VC-SDL2-image package from
[here](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip).
You need to, again, move all files from the "include" directory inside of the zip
file to the "include/SDL2" directory you provided and do the same with the files
within the "lib/x64" directory.

The VC-SDL-mixer package is now required. You can download the package from
[here](https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-VC.zip).
Again, you need to move all files from the "include" directory of the zip file
to the "include/SDL2" directory you provided. Do the same with the files
inside the "lib/x64" directory.

## Compiling

### Windows

Now you are ready to compile the files with the provided Makefile. Just run the
following command:

```shell
make all
```

The program can now be executed.
