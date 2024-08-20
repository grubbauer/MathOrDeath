#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>
#include <string>

#include "random.h"

// Window variables
int SCR_WIDTH = 0;
int SCR_HEIGHT = 0;

// General global variables
const std::string VERSION = "v0.3.0";
std::string inputedString;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

Mix_Music *sMusic = NULL;

TTF_Font *fFont;

int Operator;

void initialise();
void loadAssets();
void quit();

// Texture class
class cTexture {
 public:
  cTexture();   // Constructor
  ~cTexture();  // Destructor

  void loadFromFile(std::string path);
  void loadFromText(std::string text, SDL_Color color);
  void free();
  void render(int x, int y, int w, int h);

  int getWidth();
  int getHeight();

 private:
  SDL_Texture *mTexture;
  int mHeight;
  int mWidth;
};

// Class objects
cTexture gTestBackground;
cTexture gFontTexture;

cTexture::cTexture() {
  mTexture = NULL;
  mHeight = 0;
  mWidth = 0;
}

cTexture::~cTexture() { free(); }

void cTexture::loadFromFile(std::string path) {
  free();
  SDL_Surface *oldSurface = IMG_Load(path.c_str());
  if (oldSurface != NULL) {
    mTexture = SDL_CreateTextureFromSurface(gRenderer, oldSurface);
    mWidth = oldSurface->w;
    mHeight = oldSurface->h;
    SDL_FreeSurface(oldSurface);
  }
}

void cTexture::loadFromText(std::string text, SDL_Color color) {
  free();

  SDL_Surface *textSurface = TTF_RenderText_Solid(fFont, text.c_str(), color);
  mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  mWidth = textSurface->w;
  mHeight = textSurface->h;

  SDL_FreeSurface(textSurface);
}

void cTexture::free() {
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void cTexture::render(int x, int y, int w, int h) {
  SDL_Rect renderQuad = {x, y, w, h};
  SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int cTexture::getWidth() { return mWidth; }

int cTexture::getHeight() { return mHeight; }

int WinMain(int argc, char *argv[]) {
  initialise();
  loadAssets();

  bool stop = false;
  SDL_Event e;
  const char *pressedKey;

  while (!stop) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        stop = true;
      } else if (e.type == SDL_KEYDOWN) {
        SDL_Keycode pressedKeyRaw = e.key.keysym.sym;

        if (pressedKeyRaw >= SDLK_0 && pressedKeyRaw <= SDLK_9) {
          pressedKey = SDL_GetKeyName(pressedKeyRaw);
          inputedString += pressedKey;  // Accumulate the number as a string

          gFontTexture.loadFromText(inputedString, {255, 255, 255});
        }
      }
    }

    // Game logic
    /*
    Operator = randNum(1,4);
    switch (Operator) {
        case 1:
            printf("+");
            break;
        case 2:
            printf("-");
            break;
        case 3:
            printf("*");
            break;
        case 4:
            printf("/");
            break;
    }
    */
    // Graphical rendering
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    gTestBackground.render(0, 0, SCR_WIDTH, SCR_HEIGHT);
    gFontTexture.render(0, 0, gFontTexture.getWidth(),
                        gFontTexture.getHeight());
    SDL_RenderPresent(gRenderer);

    // Sounds
    if (Mix_PlayingMusic() == 0) {
      Mix_PlayMusic(sMusic, -1);
    }
  }

  quit();
  return 0;
}

void initialise() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  IMG_Init(IMG_INIT_PNG);  // Currently only the png format is needed
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  TTF_Init();

  // Get the current display mode of the primary display
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);

  SCR_WIDTH = display_mode.w;
  SCR_HEIGHT = display_mode.h;

  gWindow = SDL_CreateWindow(("MathOrDeath " + VERSION).c_str(),
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
  gRenderer = SDL_CreateRenderer(
      gWindow, -1,
      SDL_RENDERER_ACCELERATED |
          SDL_RENDERER_PRESENTVSYNC);  // Accelerated with VSync activated
  SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void loadAssets() {
  // Graphical elements
  gTestBackground.loadFromFile("res/img/background/test-0001.png");

  // Sounds
  sMusic = Mix_LoadMUS("res/sfx/music/test.ogg");

  // Fonts
  fFont = TTF_OpenFont("res/font/PressStart2P-Regular.ttf", 20);
  gFontTexture.loadFromText(
      "Als Gregor Samsa eines Morgens aus unruhigen Traeumen erwachte",
      {0, 0, 0});
}

void quit() {
  // Graphical elements
  gTestBackground.free();

  // Sounds
  Mix_FreeMusic(sMusic);

  // SDL Elements
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);

  /*
   *  Special attention: If IMG_Quit does NOT work when working with CMake,
   * change #include "close_code.h" on line 2191 to #include <close_code.h>.
   * This will typically resolve the issue.
   */
  IMG_Quit();
  Mix_Quit();
  SDL_Quit();

  Operator = NULL;
}
