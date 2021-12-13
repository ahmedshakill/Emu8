//
// Created by kingpin on 12/13/2021.
//

#ifndef EMU8_CONTROLLER_H
#define EMU8_CONTROLLER_H

#include <SDL.h>
#include "menu.h"
#include "game.h"
#include "chip8.h"
#include <string>
#include <array>
class Controller{
public:
    Controller();
    void Control();
    ~Controller();

private:
    void GetDisplayInfo();
    void InitMenu();
    void DeleteMenu();
    void InitGame();
    void DeleteGame();
    void InitChip8();
    void DeleteChip8();
    void ClearEvents();
    void GameLoop();

private:
    Menu* menu = nullptr;
    Game* game = nullptr;
    Chip8* chip8 = nullptr;
    SDL_DisplayMode display_mode = {0};

private:
    static const int numOfRoms=25;
    std::array<std::string,numOfRoms > roms={};
    std::string romfile{"INVADERS"};
    int videoPitch;
    bool quit=false;
    int selectedRom{};
    SDL_Event event;
    int cycleDelay = 1;
};


#endif //EMU8_CONTROLLER_H
