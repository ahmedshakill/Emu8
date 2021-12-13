//
// Created by kingpin on 12/11/2021.
//

#ifndef EMU8_GAME_H
#define EMU8_GAME_H
#include <SDL.h>
class Game
{
public:
    Game(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
    ~Game();
    void Update(void const* buffer, int pitch);
    bool ProcessInput(uint8_t* keys);
private:
    int windowWidth;
    int windowHeight;
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture*  texture{};
    SDL_Texture*  keypadTexture{};
    SDL_Surface * keypadSurface {};
    SDL_Rect keypadRect{};
    SDL_Rect gameRect{};
    int xpos{};
    int ypos{};

};

#endif //EMU8_GAME_H
