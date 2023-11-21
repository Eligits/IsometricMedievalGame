#include <SDL2/SDL.h>

struct Vector2 {
    float x;
    float y;
};

class Tile {
public:
    Tile(SDL_Renderer *renderer, int spriteWidth, int spriteHeight);
    ~Tile();
    Vector2 to_screen_coordinate(Vector2 tile);
    void SpawnTile(int SCREEN_WIDTH, int SCREEN_HEIGHT, int spriteSizeX, int spriteSizeY);
private:
    SDL_Surface  *tileFile = NULL;
    SDL_Texture  *texture = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect tilePos;
    const float i_x = 1;
    const float i_y = 0.5;
    const float j_x = -1;
    const float j_y = 0.5;
    int spriteWidth;
    int spriteHeight;
    
};