#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int SCR_WIDTH = 640;
const int SCR_HEIGHT = 480;

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

void initialise();
void quit();

void initialise() {
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("MathOrDeath v.0.0.1-2-nf",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCR_WIDTH,SCR_HEIGHT,SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

int main(int argc, char* argv[]) {
    return 0;
}