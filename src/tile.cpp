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
}

Vector2 Tile::to_screen_coordinate(Vector2 tile) {
    Vector2 result;
    result.x = tile.x * i_x * 0.5f * spriteWidth + tile.y * j_x * 0.5f * spriteWidth;
    result.y = tile.x * i_y * 0.5f * spriteHeight + tile.y * j_y * 0.5f * spriteHeight;
    return result;
};



struct Matrix2x2 {
    float a, b, c, d;
};

Matrix2x2 invert_matrix(float a, float b, float c, float d) {
    float det = 1.0f / (a * d - b * c);
    return {det * d, det * -b, det * -c, det * a};
}

Vector2 to_grid_coordinate(const Vector2& screen, float i_x, float j_x, float i_y, float j_y, float w, float h) {
    float a = i_x * 0.5f * w;
    float b = j_x * 0.5f * w;
    float c = i_y * 0.5f * h;
    float d = j_y * 0.5f * h;

    Matrix2x2 inv = invert_matrix(a, b, c, d);
    return {
        screen.x * inv.a + screen.y * inv.b,
        screen.x * inv.c + screen.y * inv.d
    };
}




void Tile::SpawnTileChunk(int chunkStartX, int chunkStartY) {
    int chunkSize = 15;
    int startX = chunkStartX / 2 - spriteWidth / 2;
    int startY = 0;
    for (int i = 0; i < chunkSize; ++i) {
        
        for (int j = 0; j < chunkSize; ++j) {
            Vector2 gridPos = {static_cast<float>(i), static_cast<float>(j)};
            Vector2 screenCoord = to_screen_coordinate(gridPos);


            // Create an SDL_Rect at the screen coordinates for rendering
            screenCoord.x += startX;
            screenCoord.y += startY;

            tile_Pos_Size = {static_cast<int>(screenCoord.x), static_cast<int>(screenCoord.y), spriteWidth, spriteHeight};
            SDL_RenderCopy(renderer, texture, NULL, &tile_Pos_Size);
        }
    }
    SDL_RenderPresent(renderer); // Call this once after rendering all tiles
}

void Tile::mainMouseLoop(SDL_Event e) {
    Vector2 screenCoord = { static_cast<float>(e.motion.x), static_cast<float>(e.motion.y) };
    mouseOverGridCoord  = to_grid_coordinate(screenCoord, i_x, j_x, i_y, j_y, spriteWidth, spriteHeight);
    std::cout << "Grid Coordinate: (" << static_cast<int>(mouseOverGridCoord.x) << ", " << static_cast<int>(mouseOverGridCoord.y) << ")" << std::endl;
    //  if (gridPos.x == mouseOverGridCoord.x && gridPos.y == mouseOverGridCoord.y) {
    //             startY = -10; // Raise the tile up
    //         } else {
    //             startY = 0; // Normal position
    //         }       
}
    

Tile::~Tile() {
    SDL_DestroyTexture(texture);
    IMG_Quit();
}

