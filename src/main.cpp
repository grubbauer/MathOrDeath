/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <shlobj.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <atomic>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>

#include "grubbauer/equation.h"
#include "grubbauer/random.h"
#include "grubbauer/savefile.h"
#include "grubbauer/assetpacks.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

const std::string VERSION = "v1.3.0";

// Window variables
int SCR_WIDTH = 0;
int SCR_HEIGHT = 0;

// General global variables
int lvl = 1;
std::atomic<int> spriteIndex = {10};
std::atomic<bool> stopTimer = {false};
std::string inputedString;
std::string equation = grubbauer::getRandomEquation(lvl);
std::atomic<int> remainingTime = {11};
std::atomic<bool> answeredCorrect = {false};
std::atomic<bool> runTimerVar = {false};
bool displaySplashScreen = true;
bool isFullscreen = false;
float equationResult = grubbauer::getEquationAnswer(equation);
bool answeredWrong = false;
Uint32 answeredCorrectTime = 0;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

// Colors
SDL_Color cBlack = {0, 0, 0};

// Music
Mix_Music *sMusic = NULL;

// Soundeffect
Mix_Chunk *sSplash = NULL;

// Fonts
TTF_Font *fInput;
TTF_Font *fEquation;
TTF_Font *fHighscores;

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
cTexture gBoard;

// Spritesheet rect's
SDL_Rect rTimer[11];
SDL_Rect rCorrect[2];

// Font Textures
cTexture gInputFontTexture;
cTexture gEquationFontTexture;
cTexture gHighscoreFontTexture;

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

int main(int argc, char *argv[]) {
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
            gInputFontTexture.loadFromText(inputedString, cBlack, fInput);
            break;
          }
          case SDLK_MINUS: {
            inputedString += '-';
            gInputFontTexture.loadFromText(inputedString, cBlack, fInput);
            break;
          }
          case SDLK_PERIOD: {
            inputedString += '.';
            gInputFontTexture.loadFromText(inputedString, cBlack, fInput);
            break;
          }
          case SDLK_COMMA: {
            inputedString += '.';
            gInputFontTexture.loadFromText(inputedString, cBlack, fInput);
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

              // Compare the rounded values
              if (roundedUserAnswer == roundedEquationResult) {
                lvl++;
                equation = grubbauer::getRandomEquation(lvl);
                equationResult = grubbauer::getEquationAnswer(equation);
                gEquationFontTexture.loadFromText(equation, cBlack, fEquation);
                inputedString.clear();  // Clear the string after correct input
                gInputFontTexture.free();  // Optionally clear the texture
                answeredCorrect = true;
                answeredCorrectTime = SDL_GetTicks();
              } else {
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
                gInputFontTexture.loadFromText(inputedString, cBlack, fInput);
              }
            }
            break;
          }
          case SDLK_F11: {
            if (isFullscreen) {
              SDL_SetWindowFullscreen(gWindow, 0);
              SCR_WIDTH = 1280;
              SCR_HEIGHT = 720;
              isFullscreen = false;
            } else if (!isFullscreen) {
              SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
              SDL_DisplayMode display_mode;
              SDL_GetCurrentDisplayMode(0, &display_mode);
              SCR_WIDTH = display_mode.w;
              SCR_HEIGHT = display_mode.h;
              isFullscreen = true;
              break;
            }

            TTF_SetFontSize(fInput, (SCR_WIDTH / 30));
            TTF_SetFontSize(fEquation, (SCR_WIDTH / 55));

            gInputFontTexture.loadFromText(" ", {0, 0, 0}, fInput);
            gEquationFontTexture.loadFromText(equation, {0, 0, 0}, fEquation);
          }
        }
      }
    }

    Uint32 currentTime = SDL_GetTicks();

    // Graphical rendering
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    if (displaySplashScreen) {
      Mix_PlayChannel(-1, sSplash, 0);
      Uint32 splashStartTime = SDL_GetTicks();
      bool splashRunning = true;

      while (splashRunning) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            stop = true;
            splashRunning = false;
          } else if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) {
            splashRunning = false;
            Mix_HaltChannel(-1);
          }
        }

        // Render the splash screen
        gSplashScreen.render(0, 0, SCR_WIDTH, SCR_HEIGHT);
        SDL_RenderPresent(gRenderer);

        // Exit the splash screen after a timeout (e.g., 8000 ms)
        if (SDL_GetTicks() - splashStartTime >= 8000) {
          splashRunning = false;
        }
      }

      displaySplashScreen = false;
      runTimerVar = true;
    }

    gBackgroundMain.render(0, 0, SCR_WIDTH, SCR_HEIGHT);
    gTeacher.render(0, 0, SCR_HEIGHT / 1.5, SCR_HEIGHT);
    gInputWindow.render((SCR_WIDTH - SCR_HEIGHT) / 2, SCR_HEIGHT / 3,
                        SCR_HEIGHT, SCR_HEIGHT / 0.75);
    gEquationFontTexture.render(
      (SCR_WIDTH - gEquationFontTexture.getWidth()) / 2, (SCR_HEIGHT / 1.63),
      gEquationFontTexture.getWidth(), gEquationFontTexture.getHeight());
    gInputFontTexture.render((SCR_WIDTH - gInputFontTexture.getWidth()) / 2,
                             (SCR_HEIGHT / 1.4), gInputFontTexture.getWidth(),
                             gInputFontTexture.getHeight());
    // Render the timer
    if (spriteIndex <= 10) {
      gTimer.render(SCR_WIDTH - (SCR_HEIGHT / 2), 0, SCR_HEIGHT / 2,
                    SCR_HEIGHT / 24, &rTimer[spriteIndex]);
    }
    if (spriteIndex == 10) {
      answeredWrong = true;
      grubbauer::saveSaveFile(lvl);
    }

    if (answeredWrong == true) {
      gCorrect.render((SCR_WIDTH - SCR_HEIGHT / 2.8125) / 2,
                      (SCR_HEIGHT - SCR_HEIGHT / 2.8125) / 2,
                      SCR_HEIGHT / 2.8125, SCR_HEIGHT / 2.8125, &rCorrect[1]);

      grubbauer::saveSaveFile(lvl);
      SDL_RenderPresent(gRenderer);
      SDL_Delay(500);
      gBoard.render((SCR_WIDTH - SCR_HEIGHT / 1.5) / 2,
                    (SCR_HEIGHT - SCR_WIDTH / 15) / 2, SCR_HEIGHT / 1.5,
                    SCR_WIDTH / 15);
      gHighscoreFontTexture.loadFromText(grubbauer::readSaveFile(),
                                         {255, 255, 255}, fInput);
      gHighscoreFontTexture.render(
        (SCR_WIDTH - gHighscoreFontTexture.getWidth()) / 2,
        (SCR_HEIGHT - gHighscoreFontTexture.getHeight()) / 2,
        gHighscoreFontTexture.getWidth(), gHighscoreFontTexture.getHeight());
      SDL_RenderPresent(gRenderer);
      SDL_Delay(1000);
      stop = true;
    } else if (answeredCorrect && currentTime - answeredCorrectTime <= 1000) {
      gCorrect.render((SCR_WIDTH - SCR_HEIGHT / 2.8125) / 2,
                      (SCR_HEIGHT - SCR_HEIGHT / 2.8125) / 2,
                      SCR_HEIGHT / 2.8125, SCR_HEIGHT / 2.8125, &rCorrect[0]);
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
  stopTimer = true;

  quit();
  timerThread.join();
  return 0;
}

// Required to run on windows with graphics activated
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  return main(__argc, __argv);
}

void initialize() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  IMG_Init(IMG_INIT_PNG);  // Currently only the png format is needed
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  TTF_Init();

  // Get the current display mode of the primary display
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);

  SCR_WIDTH = 1280;
  SCR_HEIGHT = 720;
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

  if (grubbauer::checkForAssetPack()) { // If AssetPack was detected
    // Graphics
    std::string assetPackDir = grubbauer::getAssetPackDirectory();
    gSplashScreen.loadFromFile(assetPackDir + "/res/img/splash/splashMaster-0001.png");
    gBackgroundMain.loadFromFile(assetPackDir + "/res/img/background/backgroundMaster-0001.png");
    gInputWindow.loadFromFile(assetPackDir + "/res/img/notepad/notepadMaster-0001.png");
    gTeacher.loadFromFile(assetPackDir + "/res/img/character/teacherMaster-0001.png");
    gTimer.loadFromFile(assetPackDir + "/res/img/bar/timerBar-0001.png");
    gCorrect.loadFromFile(assetPackDir + "/res/img/misc/correctnessIndicator-0001.png");
    gBoard.loadFromFile(assetPackDir + "/res/img/board/boardMaster-0001.png");

    // Audio
    sMusic = Mix_LoadMUS((assetPackDir + "/res/sfx/music/mainMaster-0001.ogg").c_str());
    sSplash = Mix_LoadWAV((assetPackDir + "res/sfx/splashMaster-0001.ogg").c_str());

    // Fonts
    fInput = TTF_OpenFont((assetPackDir + "/res/font/GPixel_v1.0.0.ttf").c_str(), (SCR_WIDTH / 30));
    fEquation = TTF_OpenFont((assetPackDir + "/res/font/GPixel_v1.0.0.ttf").c_str(), (SCR_WIDTH / 55));
    fHighscores = TTF_OpenFont((assetPackDir + "/res/font/GPixel_v1.0.0.ttf").c_str(), (SCR_WIDTH / 10));
    
  } else {
    // Graphics
    gSplashScreen.loadFromFile("res/img/splash/splashMaster-0001.png");
    gBackgroundMain.loadFromFile("res/img/background/backgroundMaster-0001.png");
    gInputWindow.loadFromFile("res/img/notepad/notepadMaster-0001.png");
    gTeacher.loadFromFile("res/img/character/teacherMaster-0001.png");
    gTimer.loadFromFile("res/img/bar/timerBar-0001.png");
    gCorrect.loadFromFile("res/img/misc/correctnessIndicator-0001.png");
    gBoard.loadFromFile("res/img/board/boardMaster-0001.png");

    // Audio
    sMusic = Mix_LoadMUS("res/sfx/music/mainMaster-0001.ogg");
    sSplash = Mix_LoadWAV("res/sfx/splashMaster-0001.ogg");

    // Fonts
    fInput = TTF_OpenFont("res/font/GPixel_v1.0.0.ttf", (SCR_WIDTH / 30));
    fEquation = TTF_OpenFont("res/font/GPixel_v1.0.0.ttf", (SCR_WIDTH / 55));
    fHighscores = TTF_OpenFont("res/font/GPixel_v1.0.0.ttf", (SCR_WIDTH / 10));
  }

  // Font textures
  gInputFontTexture.loadFromText(" ", {0, 0, 0}, fInput);
  gEquationFontTexture.loadFromText(equation, {0, 0, 0}, fEquation);
  gHighscoreFontTexture.loadFromText(" ", {255, 255, 255}, fHighscores);
}

void setupSpritesheets() {
  // Timer bar spritesheet
  for (int i = 0; i <= 10; i++) {
    rTimer[i].x = 0;
    rTimer[i].y = (i * 30) + (i * 4);
    rTimer[i].w = 360;
    rTimer[i].h = 30;
  }

  // Correctness Indicator spritesheet
  for (int i = 0; i <= 1; i++) {
    rCorrect[i].x = (i * 32) + (i * 4);
    rCorrect[i].y = 0;
    rCorrect[i].w = 32;
    rCorrect[i].h = 32;
  }
}

void runTimer() {
  spriteIndex.store(0);
  while (!stopTimer.load()) {
    if (!answeredCorrect.load() && runTimerVar) {
      if (remainingTime > 0) {
        remainingTime--;  // Decrement the timer
        spriteIndex.fetch_add(1);  // Update the sprite index
        // Sleep for 1 seconds
        std::this_thread::sleep_for(std::chrono::seconds(1));
      } else {
        stopTimer = true;
        answeredWrong = true;  // Time's up, mark as wrong
      }
    } else {
      // Wait a bit before checking again
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

  IMG_Quit();
  Mix_Quit();
  SDL_Quit();
}
