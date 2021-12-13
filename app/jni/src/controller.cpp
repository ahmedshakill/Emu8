//
// Created by kingpin on 12/13/2021.
//

#include "controller.h"

Controller::Controller():roms{
    "15PUZZLE","BLINKY","BLITZ", "BRIX",
    "CONNECT4","GUESS","HIDDEN","INVADERS",
    "KALEID","MAZE","MERLIN","MISSILE",
    "PONG","PONG2","PUZZLE","SYZYGY",
    "TANK","TETRIS","TICTAC","UFO",
    "VBRIX","VERS","WIPEOFF"
} {
    GetDisplayInfo();
//    InitMenu();
//    InitChip8();
//    InitGame();
}

void Controller::GetDisplayInfo() {
    SDL_DisplayMode best_display_mode = {0};
    for (int32_t display_mode_num = 0; display_mode_num < SDL_GetNumVideoDisplays(); ++display_mode_num) {
        if (SDL_GetCurrentDisplayMode(display_mode_num, &display_mode) < 0) {
            // TODO(Ryan): Logging
        }
        if (display_mode.w * display_mode.h > best_display_mode.w * best_display_mode.h) {
            best_display_mode = display_mode;
        }
        if (display_mode.w * display_mode.h == best_display_mode.w * best_display_mode.h &&
            display_mode.refresh_rate > best_display_mode.refresh_rate) {
            best_display_mode = display_mode;
        }
    }

}

void Controller::InitMenu() {
        menu=new Menu("EmuChip8",display_mode.w,display_mode.h);
}

void Controller::InitGame() {
    game = new Game("EmuChip8",display_mode.w,display_mode.h,chip8->VIDEO_WIDTH,chip8->VIDEO_HEIGHT);
}

void Controller::InitChip8() {
    chip8 = new Chip8();
    chip8->LoadROM(romfile.c_str());
    videoPitch = sizeof(chip8->video[0]) * chip8->VIDEO_WIDTH;
}
Controller::~Controller() {
    delete menu;
    delete game;
    delete chip8;
}

void Controller::ClearEvents(){
    while (SDL_PollEvent(&event)) ;
}

void Controller::GameLoop()
{
    while(!quit){
        quit = game->ProcessInput(chip8->keypad);
            chip8->Cycle();
            game->Update(chip8->video, videoPitch);
    }
    quit=false;
}

void Controller::Control() {
    InitMenu();
    while(!quit){
        selectedRom= menu->getSelectedRom();
        quit=menu->quit;
        DeleteMenu();
        ClearEvents();

        if(quit) return;

        romfile=roms[selectedRom];

        InitChip8();
        InitGame();

        GameLoop();
        ClearEvents();
        DeleteChip8();
        DeleteGame();
        InitMenu();
        ClearEvents();
    }

}

void Controller::DeleteMenu() {
    delete menu;
}

void Controller::DeleteGame() {
    delete game;
}

void Controller::DeleteChip8() {
delete chip8;
}
