#include <stdlib.h>
#include "tile.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;



Tile::Tile(SDL_Renderer *renderer, int spriteWidth, int spriteHeight) {

    IMG_Init(IMG_INIT_PNG);
    texture = IMG_LoadTexture(renderer, "images/Blue_Tile.png");
    this->renderer = renderer;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    tilePos.x = 1;
    tilePos.y = 1;
    tilePos.w = spriteWidth;
    tilePos.h = spriteHeight;
}

Vector2 Tile::to_screen_coordinate(Vector2 tile) {
    Vector2 result;
    result.x = tile.x * i_x * 0.5f * spriteWidth + tile.y * j_x * 0.5f * spriteWidth;
    result.y = tile.x * i_y * 0.5f * spriteHeight + tile.y * j_y * 0.5f * spriteHeight;
    return result;
};


void Tile::SpawnTile(int x, int y, int spriteWidth, int spriteHeight) {
    double testX = (tilePos.x * i_x * 0.5 * spriteWidth + tilePos.y * (1 * 0.5 * spriteWidth));
    double testY = (tilePos.x * i_y * 0.5 * spriteHeight + tilePos.y * (j_y * 0.5 * spriteHeight));
    // double testX = tilePos.x * i_x + tilePos.y * 1;
    // double testY = tilePos.y * i_y + tilePos.y * j_y;
    
    // Vector2 screenCoord = to_screen_coordinate(Tile(i));

    for (int i = 0; i <= x; i += spriteWidth) {
        SDL_RenderCopy(renderer, texture, NULL, &tilePos);
        SDL_RenderPresent(renderer);
        
        for (int index = 0; index <= y; index += spriteHeight) {
            SDL_RenderCopy(renderer, texture, NULL, &tilePos);
            SDL_RenderPresent(renderer);
            tilePos.y += testY;
        }

    tilePos.x += testX;
    cout << testX << endl;
    tilePos.y = 0;
    }
};

Tile::~Tile() {
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
}

