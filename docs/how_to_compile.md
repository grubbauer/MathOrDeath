# How to compile

## Windows

### Software

1. Download MSYS2 Mingw from [this link][msys2-link]
2. Download following packages:
    * `mingw-w64-x86_64-clang`
    * `mingw-w64-x86_64-gcc`
    * `mingw-w64-x86_64-make`
3. Add your `mingw64/bin` directory to the system PATH

### Libaries

1. Download following librarys:
    * [SDL2][sdl2-link]
    * [SDL2_image][sdl2_image-link]
    * [SDL2_mixer][sdl2_mixer-link]
    * [SDL2_ttf][sdl2_ttf-link]
2. Move the contents of the `include`, `bin` and `lib` directories of each
library to the project's `include`, `bin` and `lib` directories.

[msys2-link]: https://github.com/msys2/msys2-installer/releases/download/2024-12-08/msys2-x86_64-20241208.exe
[sdl2-link]: https://github.com/libsdl-org/SDL/releases/download/release-2.30.6/SDL2-devel-2.30.6-mingw.tar.gz
[sdl2_image-link]: https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-mingw.tar.gz
[sdl2_mixer-link]: https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-mingw.tar.gz
[sdl2_ttf-link]: https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-mingw.tar.gz

### Compiling

1. Change the `MINGW_LIB_DIR` in the Makefile to your mingw32-bin.
2. Run the following command:

    ```shell
    mingw32-make
    ```

3. The file `build/windows-x64/MathOrDeath_v1.3.0.exe` can now be executed.
