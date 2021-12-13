//
// Created by kingpin on 12/13/2021.
//

#ifndef EMU8_MENU_H
#define EMU8_MENU_H
#include <SDL.h>

class Menu {
public:
    Menu(char const* title, int windowWidth, int windowHeight);
    ~Menu();
    void Update();
    bool ProcessInput();
    void RecreateWindowAndRenderer();
    void DestroyWindowAndRenderer();
    void ClearEvents();
    int getSelectedRom();
public:
    bool quit=false;
private:
    int windowWidth{};
    int windowHeight{};
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
    SDL_Rect r{};
    SDL_Surface *rgbSurface{} ;
    bool gameSelected=false;
    SDL_Event event;
    int selectionNo{};

    int halfHeight{};
    int halfWidth{};
};


#endif //EMU8_MENU_H
