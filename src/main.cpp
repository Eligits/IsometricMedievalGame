#include <stdlib.h>
#include <SDL2/SDL.h>


#include "tile.h"
#include <iostream>

using namespace std;
int spriteWidth = 64;
int spriteHeight = 64;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_WIDTH = 1920;

int main(void) {
    // Set SDL Window and SDL Renderer
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        SCREEN_WIDTH, SCREEN_HEIGHT,
        0, &window, &renderer
   );

    // Create the Tile object
    Tile tile(renderer, spriteWidth, spriteHeight);
    tile.SpawnTile(SCREEN_WIDTH, SCREEN_HEIGHT, spriteWidth, spriteHeight);

    // Game loop
    SDL_Event event;
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return EXIT_SUCCESS;

    return 0;
}