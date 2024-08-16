#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

// General global variables
const int SCR_WIDTH = 640;
const int SCR_HEIGHT = 480;
const std::string VERSION = "v.0.0.1-14";

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

Mix_Music* sMusic = NULL;   

int Operator;

void initialise();
void loadAssets();
int getRandOperator();
void quit();

// Texture class
class cTexture {
public:
    cTexture(); // Constructor
    ~cTexture(); // Destructer
    
    void loadFromFile(std::string path);
    void free();
    void render(int x, int y, SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;
    int mHeight;
    int mWidth;
};

// Class objects
cTexture gTestBackground;

cTexture::cTexture() {
    mTexture = NULL;
    mHeight = 0;
    mWidth = 0;
}

cTexture::~cTexture() {
    free();
}

void cTexture::loadFromFile(std::string path) {
    free();
    SDL_Surface* oldSurface = IMG_Load(path.c_str());
    if (oldSurface != NULL) {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, oldSurface);
        mWidth = oldSurface->w;
        mHeight = oldSurface->h;
        SDL_FreeSurface(oldSurface);
    }
}

void cTexture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void cTexture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderAreaRect = { x, y, mWidth, mHeight };
    if (clip != NULL) {
        renderAreaRect.w = clip->w;
        renderAreaRect.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderAreaRect);
}

int cTexture::getWidth() {
    return mWidth;
}

int cTexture::getHeight() {
    return mHeight;
}

int WinMain(int argc, char* argv[]) {
    initialise();
    loadAssets();

    bool stop = false;
    SDL_Event e;

    

    while (!stop) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                stop = true;
            }
        }

        // Game logic
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

        // Graphical rendering
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);
        gTestBackground.render(0,0);
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
    IMG_Init(IMG_INIT_PNG); // Currently only the png format is needed
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    gWindow = SDL_CreateWindow(("MathOrDeath " + VERSION).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Accelerated with VSync activated
    SDL_SetWindowFullscreen(gWindow,SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void loadAssets() {
    gTestBackground.loadFromFile("res/img/misc/background-0002.png");   
    sMusic = Mix_LoadMUS("res/sfx/music/test.ogg");
}

void quit() {

    // Graphical elements
    gTestBackground.free();

    // Sounds
    Mix_FreeMusic(sMusic);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    /*
     *  Special attention: If IMG_Quit does NOT work when working with CMake, change #include "close_code.h" on line 2191 to 
     *  #include <close_code.h>. This will typically resolve the issue. 
    */  
    IMG_Quit();
    SDL_Quit();

    Operator = NULL;
}
