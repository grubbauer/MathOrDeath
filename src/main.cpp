/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.2.0
 * See LICENSE.md file in the project root for full license information.
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include <atomic>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>

#include "equation_answer.h"
#include "generate_equation.h"

const std::string VERSION = "v0.9.2-alpha";

// Window variables
int SCR_WIDTH = 0;
int SCR_HEIGHT = 0;

// General global variables
int lvl = 1;
std::atomic<int> spriteIndex(10);
std::atomic<bool> stopTimer(false);
std::string inputedString;
std::string equation = randEquation(lvl);
std::atomic<int> remainingTime(11);
float equationResult = getEquationAnswer(equation);
bool answeredWrong = false;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

Mix_Music *sMusic = NULL;

TTF_Font *fInput;
TTF_Font *fEquation;

void initialise();
void loadAssets();
void setupSpritesheets();
void runTimer();
void quit();

// Texture class
class cTexture {
  public:
  cTexture();  // Constructor
  ~cTexture();  // Destructor

  void loadFromFile(std::string path);
  void loadFromText(std::string text, SDL_Color color, TTF_Font *font);
  void free();
  void render(int x, int y, int w, int h, SDL_Rect *clip = NULL);

  int getWidth();
  int getHeight();

  private:
  SDL_Texture *mTexture;
  int mHeight;
  int mWidth;
};

// Class objects
cTexture gBackgroundMain;
cTexture gInputWindow;
cTexture gTeacher;
cTexture gTimer;
cTexture gCorrect;

// Spritesheet rect's
SDL_Rect rTimer[11];
SDL_Rect rCorrect[2];

// Font Textures
cTexture gInputFontTexture;
cTexture gEquationFontTexture;

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

void cTexture::loadFromText(std::string text, SDL_Color color, TTF_Font *font) {
  free();

  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
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

void cTexture::render(int x, int y, int w, int h, SDL_Rect *clip) {
  SDL_Rect renderQuad = {x, y, w, h};  // Target render area

  // Scale render area to target width and height
  if (clip != NULL) {
    SDL_Rect srcRect = {clip->x, clip->y, clip->w,
                        clip->h};  // Source rectangle
    SDL_RenderCopy(gRenderer, mTexture, &srcRect,
                   &renderQuad);  // Use clip as source
  } else {
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);  // No clipping
  }
}

int cTexture::getWidth() { return mWidth; }

int cTexture::getHeight() { return mHeight; }

int WinMain(int argc, char *argv[]) {
  initialise();
  loadAssets();
  setupSpritesheets();

  // Start the timer thread
  std::thread timerThread(runTimer);

  bool stop = false;
  SDL_Event e;

  while (!stop) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        stop = true;
      } else if (e.type == SDL_KEYDOWN) {
        SDL_Keycode pressedKeyRaw = e.key.keysym.sym;
        const char *pressedKey = SDL_GetKeyName(pressedKeyRaw);

        switch (pressedKeyRaw) {
          case SDLK_0 ... SDLK_9: {
            inputedString += pressedKey;
            gInputFontTexture.loadFromText(inputedString, {255, 255, 255},
                                           fInput);
            break;
          }
          case SDLK_MINUS: {
            inputedString += '-';
            gInputFontTexture.loadFromText(inputedString, {255, 255, 255},
                                           fInput);
            break;
          }
          case SDLK_PERIOD: {
            inputedString += '.';
            gInputFontTexture.loadFromText(inputedString, {255, 255, 255},
                                           fInput);
            break;
          }
          case SDLK_RETURN: {
            try {
              float userAnswer =
                std::stof(inputedString);  // Convert input to float

              // Round both values to two decimal places
              float roundedUserAnswer = std::floorf(userAnswer * 100) / 100;
              float roundedEquationResult =
                std::floorf(equationResult * 100) / 100;

              printf("%f", roundedEquationResult);
              printf("%f", equationResult);
              // Compare the rounded values
              if (roundedUserAnswer == roundedEquationResult) {
                printf("Correct!\n");
                lvl++;
                equation = randEquation(lvl);
                equationResult = getEquationAnswer(equation);
                gEquationFontTexture.loadFromText(equation, {255, 255, 255},
                                                  fEquation);
                inputedString.clear();  // Clear the string after correct input
                gInputFontTexture.free();  // Optionally clear the texture
              } else {
                printf("Wrong!\n");
                answeredWrong = true;
              }
            } catch (const std::invalid_argument &e) {
              std::cerr << "Invalid input for checking equation: "
                        << inputedString << std::endl;
            }
            break;
          }
          case SDLK_BACKSPACE: {
            if (!inputedString.empty()) {
              inputedString =
                inputedString.substr(0, inputedString.length() - 1);

              if (inputedString.empty()) {
                gInputFontTexture.free();
              } else {
                gInputFontTexture.loadFromText(inputedString, {255, 255, 255},
                                               fInput);
              }
            }
          }
        }
      }
    }

    // Graphical rendering
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    // Render graphical elements
    gBackgroundMain.render(0, 0, SCR_WIDTH, SCR_HEIGHT);
    gTeacher.render(((SCR_WIDTH - (SCR_WIDTH / 4)) / 2), (SCR_HEIGHT / 30),
                    (SCR_WIDTH / 4), (SCR_HEIGHT));
    gInputWindow.render(((SCR_WIDTH - (SCR_WIDTH / 1.5)) / 2),
                        ((SCR_HEIGHT - (SCR_HEIGHT / 4)) / 1.3),
                        (SCR_WIDTH / 1.5), (SCR_HEIGHT / 4));
    gEquationFontTexture.render(
      (SCR_WIDTH - gEquationFontTexture.getWidth()) / 2, (SCR_HEIGHT / 1.63),
      gEquationFontTexture.getWidth(), gEquationFontTexture.getHeight());
    gInputFontTexture.render((SCR_WIDTH - gInputFontTexture.getWidth()) / 2,
                             (SCR_HEIGHT / 1.4), gInputFontTexture.getWidth(),
                             gInputFontTexture.getHeight());

    // Render the timer
    if (spriteIndex >= 0) {
      gTimer.render(SCR_WIDTH - gTimer.getWidth(), SCR_HEIGHT / 50,
                    gTimer.getWidth(), gTimer.getHeight(),
                    &rTimer[spriteIndex]);
    }
    if (spriteIndex == 0) {
      answeredWrong = true;
    }

    if (answeredWrong == true) {
      gCorrect.render((SCR_WIDTH / 2 - (gCorrect.getWidth() * SCR_HEIGHT / 3) /
                                         gCorrect.getHeight() / 2),
                      (SCR_HEIGHT / 2 - SCR_HEIGHT / 3 / 2),
                      (gCorrect.getWidth() * SCR_HEIGHT / 3) /
                        gCorrect.getHeight(),
                      SCR_HEIGHT / 3, &rCorrect[0]);

      SDL_RenderPresent(gRenderer);
      SDL_Delay(1000);
      stop = true;
    } else {
      gCorrect.render((SCR_WIDTH / 2 - (gCorrect.getWidth() * SCR_HEIGHT / 3) /
                                         gCorrect.getHeight() / 2),
                      (SCR_HEIGHT / 2 - SCR_HEIGHT / 3 / 2),
                      (gCorrect.getWidth() * SCR_HEIGHT / 3) /
                        gCorrect.getHeight(),
                      SCR_HEIGHT / 3, &rCorrect[1]);
    }

    SDL_RenderPresent(gRenderer);

    // Sounds
    if (Mix_PlayingMusic() == 0) {
      Mix_PlayMusic(sMusic, -1);
    }
  }

  // Wait for the timer thread to finish
  stopTimer.load();
  stopTimer = true;

  quit();
  timerThread.join();
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

  SCR_WIDTH = display_mode.w / 2;
  SCR_HEIGHT = display_mode.h / 2;

  gWindow = SDL_CreateWindow(("MathOrDeath " + VERSION).c_str(),
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
  // Accelerated with VSync enabled
  gRenderer = SDL_CreateRenderer(
    gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
  // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void loadAssets() {
  // Graphical elements
  gBackgroundMain.loadFromFile("res/img/background/background-0001.png");
  gInputWindow.loadFromFile("res/img/window/window-0001.png");
  gTeacher.loadFromFile("res/img/character/teacher-0001.png");
  gTimer.loadFromFile("res/img/bar/time-0001.png");
  gCorrect.loadFromFile("res/img/misc/correctness_indicator.png");

  // Sounds
  sMusic = Mix_LoadMUS("res/sfx/music/test.ogg");

  // Fonts
  fInput = TTF_OpenFont("res/font/PressStart2P-Regular.ttf", (SCR_WIDTH / 30));
  fEquation =
    TTF_OpenFont("res/font/PressStart2P-Regular.ttf", (SCR_WIDTH / 55));

  // Font textures
  gInputFontTexture.loadFromText(" ", {0, 0, 0}, fInput);
  gEquationFontTexture.loadFromText(equation, {255, 255, 255}, fEquation);
}

void setupSpritesheets() {
  // Timer bar spritesheet
  for (int i = 0; i <= 10; i++) {
    std::cout << "Timer bar: " << i << std::endl;
    rTimer[i].x = 0;
    rTimer[i].y = (i * 30) + i;
    rTimer[i].w = 360;
    rTimer[i].h = 30;
  }

  // Correctness Indicator spritesheet
  for (int i = 0; i <= 1; i++) {
    std::cout << "Correctness Indicator: " << i << std::endl;
    rCorrect[i].x = (i * 128) + i;
    rCorrect[i].y = 0;
    rCorrect[i].w = 128;
    rCorrect[i].h = 128;
  }
}

void runTimer() {
  // Decrement immididately to avoid first long frame (annoying!)
  remainingTime--;
  spriteIndex.store(remainingTime);
  std::cout << "Timer updated: " << spriteIndex.load() << std::endl;

  while (remainingTime > 0 && !stopTimer.load()) {
    for (int i = 0; i <= 9; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      if (stopTimer.load()) {
        break;
      }
    }
    remainingTime--;

    spriteIndex.store(remainingTime);
    std::cout << "Timer updated: " << spriteIndex.load() << std::endl;
  }

  std::cout << "Time's up!" << std::endl;
}

void quit() {
  // Graphical elements
  gBackgroundMain.free();
  gInputWindow.free();
  gEquationFontTexture.free();
  gInputFontTexture.free();
  gTeacher.free();
  gTimer.free();
  gCorrect.free();

  // Sounds
  Mix_FreeMusic(sMusic);

  // Fonts
  TTF_CloseFont(fInput);
  TTF_CloseFont(fEquation);

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
}
