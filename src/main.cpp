#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

const int SCR_WIDTH = 640;
const int SCR_HEIGHT = 480;

SDL_Window *gWindow;
SDL_Renderer *gRenderer;

void initialise();
void quit();

int main(int argc, char *argv[]) {
    initialise();

    bool stop = false;
    SDL_Event e;

    while (!stop) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                stop = true;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);
    }

    quit();
    return 0;
}

void initialise() {
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("MathOrDeath v.0.0.1-4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void quit() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    SDL_Quit();
}