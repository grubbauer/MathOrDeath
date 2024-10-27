/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.2.0
 * See LICENSE.md file in the project root for full license information.
*/
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

const std::string VERSION = "v1.0.0";

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
std::atomic<bool> answeredCorrect = false;
std::atomic<bool> runTimerVar =  false;
bool displaySplashScreen = true;
float equationResult = getEquationAnswer(equation);
bool answeredWrong = false;
Uint32 answeredCorrectTime = 0;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

// Music
Mix_Music *sMusic = NULL;

// Soundeffect
Mix_Chunk *sSplash = NULL;

// Fonts
TTF_Font *fInput;
TTF_Font *fEquation;

void initialize();
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
cTexture gSplashScreen;
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

  if (clip != NULL) {
    float clipAspect = (float)clip->w / (float)clip->h;
    float targetAspect = (float)w / (float)h;

    if (targetAspect > clipAspect) {
      renderQuad.w = h * clipAspect;
    } else if (targetAspect < clipAspect) {
      renderQuad.h = w / clipAspect;
    }
  }

  // Render the texture
  if (clip != NULL) {
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
  } else {
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
  }
}

int cTexture::getWidth() { return mWidth; }

int cTexture::getHeight() { return mHeight; }

int WinMain(int argc, char *argv[]) {
  initialize();
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
                answeredCorrect = true;
                answeredCorrectTime = SDL_GetTicks();
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

    Uint32 currentTime = SDL_GetTicks();

    // Graphical rendering
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    

    if (displaySplashScreen) {
      gSplashScreen.render(0,0, SCR_WIDTH, SCR_HEIGHT);
      std::cout << "Splash screen render logic ran!" << std::endl;
      SDL_RenderPresent(gRenderer);
      std::cout << "Refreshed renderer!" << std::endl;
      Mix_PlayChannel(-1, sSplash, 0);
      std::cout << "Music played" << std::endl;
      SDL_Delay(1500);
      displaySplashScreen = false;
      runTimerVar = true;
    }
    // Render graphical elements
    gBackgroundMain.render(0, 0, SCR_WIDTH, SCR_HEIGHT);
    gTeacher.render(((SCR_WIDTH - (SCR_WIDTH / 4)) / 2), (SCR_HEIGHT / 30),
                    (SCR_WIDTH / 4), (SCR_HEIGHT));
    gInputWindow.render(((SCR_WIDTH - (SCR_WIDTH / 1.5)) / 2.0),
                        ((SCR_HEIGHT - (SCR_HEIGHT / 4.0)) / 1.3),
                        (SCR_WIDTH / 1.5), (SCR_HEIGHT / 4));
    gEquationFontTexture.render(
      (SCR_WIDTH - gEquationFontTexture.getWidth()) / 2, (SCR_HEIGHT / 1.63),
      gEquationFontTexture.getWidth(), gEquationFontTexture.getHeight());
    gInputFontTexture.render((SCR_WIDTH - gInputFontTexture.getWidth()) / 2,
                             (SCR_HEIGHT / 1.4), gInputFontTexture.getWidth(),
                             gInputFontTexture.getHeight());

    // Render the timer
    if (spriteIndex <= 10) {
      gTimer.render(SCR_WIDTH - gTimer.getWidth(), 0, SCR_HEIGHT / 2,
                    SCR_HEIGHT / 24, &rTimer[spriteIndex]);
    }
    if (spriteIndex == 10) {
      answeredWrong = true;
    }

    if (answeredWrong == true) {
      gCorrect.render((SCR_WIDTH - SCR_HEIGHT / 2.8125) / 2,
                      (SCR_HEIGHT - SCR_HEIGHT / 2.8125) / 2,
                      SCR_HEIGHT / 2.8125, SCR_HEIGHT / 2.8125, &rCorrect[0]);
      SDL_RenderPresent(gRenderer);
      SDL_Delay(1000);
      stop = true;
    } else if (answeredCorrect && currentTime - answeredCorrectTime <= 1000) {
      gCorrect.render((SCR_WIDTH - SCR_HEIGHT / 2.8125) / 2,
                      (SCR_HEIGHT - SCR_HEIGHT / 2.8125) / 2,
                      SCR_HEIGHT / 2.8125, SCR_HEIGHT / 2.8125, &rCorrect[1]);
      spriteIndex = 0;
      remainingTime = 11;
    } else {
      answeredCorrect = false;
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

void initialize() {
  
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  IMG_Init(IMG_INIT_PNG);  // Currently only the png format is needed
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  TTF_Init();

  // Get the current display mode of the primary display
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);

  SCR_WIDTH = display_mode.w / 2;
  SCR_HEIGHT = display_mode.h / 2;
  std::cout << "Screen_WIDTH:" << SCR_WIDTH << "\n";
  std::cout << "Screen_HEIGHT:" << SCR_HEIGHT << "\n";
  gWindow = SDL_CreateWindow(("MathOrDeath " + VERSION).c_str(),
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
  // Accelerated with VSync enabled
  gRenderer = SDL_CreateRenderer(
    gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
}

void loadAssets() {
  // Graphical elements
  gSplashScreen.loadFromFile("res/img/splash/splashMaster-0001.png");
  gBackgroundMain.loadFromFile("res/img/background/backgroundMaster-0001.png");
  gInputWindow.loadFromFile("res/img/notepad/notepadMaster-0001.png");
  gTeacher.loadFromFile("res/img/character/teacherMaster-0001.png");
  gTimer.loadFromFile("res/img/bar/timerBar-0001.png");
  gCorrect.loadFromFile("res/img/misc/correctnessIndicator-0001.png");

  // Music
  sMusic = Mix_LoadMUS("res/sfx/music/test.ogg");

  // Sounds
  sSplash = Mix_LoadWAV("res/sfx/splash.wav");

  // Fonts
  fInput = TTF_OpenFont("res/font/GPixel_v1.0.0.ttf", (SCR_WIDTH / 30));
  fEquation =
    TTF_OpenFont("res/font/GPixel_v1.0.0.ttf", (SCR_WIDTH / 55));

  // Font textures
  gInputFontTexture.loadFromText(" ", {0, 0, 0}, fInput);
  gEquationFontTexture.loadFromText(equation, {255, 255, 255}, fEquation);
}

void setupSpritesheets() {
  // Timer bar spritesheet
  for (int i = 0; i <= 10; i++) {
    std::cout << "Timer bar: " << i << std::endl;
    rTimer[i].x = 0;
    rTimer[i].y = (i * 30) + (i * 4);
    rTimer[i].w = SCR_HEIGHT / 2;
    rTimer[i].h = SCR_HEIGHT / 24;
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
    spriteIndex.store(0);
    while (!stopTimer.load()) {
        if (!answeredCorrect.load() && runTimerVar) {
            if (remainingTime > 0) {
                remainingTime--;  // Decrement the timer
                spriteIndex.fetch_add(1);  // Update the sprite index
                std::cout << spriteIndex << std::endl;
                std::cout << "Timer updated: " << remainingTime << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
            } else {
                stopTimer = true;
                answeredWrong = true;  // Time's up, mark as wrong
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Wait a bit before checking again
        }
    }
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
