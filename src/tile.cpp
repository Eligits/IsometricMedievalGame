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
    tile_Pos_Size.x = 0;
    tile_Pos_Size.y = 0;
    tile_Pos_Size.w = spriteWidth;
    tile_Pos_Size.h = spriteHeight;
}

Vector2 Tile::to_screen_coordinate(Vector2 tile) {
    Vector2 result;
    result.x = tile.x * i_x * 0.5f * spriteWidth + tile.y * j_x * 0.5f * spriteWidth;
    result.y = tile.x * i_y * 0.5f * spriteHeight + tile.y * j_y * 0.5f * spriteHeight;
    return result;
};


void Tile::SpawnTile(int gridWidth, int gridHeight) {
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            Vector2 gridPos = {static_cast<float>(i), static_cast<float>(j)};
            Vector2 screenCoord = to_screen_coordinate(gridPos);
            // Create an SDL_Rect at the screen coordinates for rendering
            tile_Pos_Size = {static_cast<int>(screenCoord.x), static_cast<int>(screenCoord.y), spriteWidth, spriteHeight};

            SDL_RenderCopy(renderer, texture, NULL, &tile_Pos_Size);
        }
    }
    SDL_RenderPresent(renderer); // Call this once after rendering all tiles
}

Tile::~Tile() {
    SDL_DestroyTexture(texture);
    IMG_Quit();
}

