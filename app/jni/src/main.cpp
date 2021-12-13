//
// Created by kingpin on 12/11/2021.
//

//#include "SDL.h"

//#include "chip8.h"
//#include "game.h"
//#include <SDL_image.h>

#include<controller.h>

#include <cstdlib>
#include <cstdint>
#include <random>
typedef uint32_t u32;
typedef uint8_t u8;
typedef int32_t i32;

int launchgame(int);

/* int
SDL_main(int argc, __attribute__ ((unused)) char* argv[argc + 1])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // TODO(Ryan): Logging
        return EXIT_FAILURE;
    }

    // IMPORTANT(Ryan): Choose display mode based on highest resolution then refresh rate.
    SDL_DisplayMode display_mode = {0};
    SDL_DisplayMode best_display_mode = {0};
    for (i32 display_mode_num = 0; display_mode_num < SDL_GetNumVideoDisplays(); ++display_mode_num) {
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
    // NOTE(Ryan): Assume fixed refresh rate
    SDL_assert(best_display_mode.refresh_rate != 0);

//    SDL_Window* window = SDL_CreateWindow(
//            "Foundation",
//            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//            best_display_mode.w, best_display_mode.h,
//            SDL_WINDOW_FULLSCREEN
//    );
//    if (window == NULL) {
//        // TODO(Ryan): Logging
//        return EXIT_FAILURE;
//    }
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (renderer == NULL) {
//        // TODO(Ryan): Logging
//        return EXIT_FAILURE;
//    }
//
//    const u8* keyboard_state = SDL_GetKeyboardState(NULL);
//
//    SDL_Texture *texture;
//    SDL_Rect r;
//    SDL_Surface *rgbSurface ;
//
//    SDL_RenderClear(renderer);
////    rgbSurface= SDL_CreateRGBSurface(0,240,480,32,0,0,0,0);
//
//    rgbSurface = IMG_Load("mountain.jpg");
//
////    r->x = 10,r->y=10,r->w=50,r->h=50;
//    r.x = 120,r.y=130,r.w=800,r.h=500;
////    SDL_FillRect(rgbSurface, nullptr,SDL_MapRGB(rgbSurface->format, 255, 0, 0));
////    texture=SDL_CreateTextureFromSurface(renderer,rgbSurface);
////    SDL_RenderCopy(renderer,texture, nullptr, &r);
////    SDL_RenderPresent(renderer);
////    SDL_Delay(4000);
//
//    bool want_to_run = true;
//    while (want_to_run) {
//        SDL_Event event = {0};
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                want_to_run = false;
//            }
//            if (keyboard_state[SDL_SCANCODE_Q]) {
//                want_to_run = false;
//            }
//
//            if(event.tfinger.type==SDL_FINGERDOWN){
//                SDL_Log("touch x=%d y=%d",event.tfinger.x,event.tfinger.y);
//            }
//
//            if(event.key.keysym.sym==SDLK_AC_BACK)
//            {
//                SDL_Log("BackButton Pressed");
//                want_to_run=false;
////                SDL_AndroidBackButton();
//            }
//        }
//
//        SDL_RenderClear(renderer);
////        SDL_SetRenderDrawColor(renderer, rand()%255, rand()%255, rand()%255, rand()%255);
//        texture=SDL_CreateTextureFromSurface(renderer,rgbSurface);
////        r={410,510,250,150};
//        SDL_RenderCopy(renderer,texture, nullptr, &r);
//        SDL_RenderPresent(renderer);
////        SDL_Delay(550);
//    }
//
//    SDL_FreeSurface(rgbSurface);
//    SDL_DestroyTexture(texture);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return EXIT_SUCCESS;

    SDL_Log("hello from the other side");

//    int cycleDelay = 10;
//    Chip8* chip8 = new Chip8();
//    const int videoScale = 20;

//    Platform platform("CHIP-8 Emulator", display_mode.w, display_mode.h, chip8->VIDEO_WIDTH, chip8->VIDEO_HEIGHT);

    //  2nd Window
    SDL_Window* window2{};
    SDL_Renderer* renderer2{};
    SDL_Texture *texture;
    SDL_Rect r;
    SDL_Surface *rgbSurface ;

    window2 = SDL_CreateWindow("2nd window", 0, display_mode.h+50, 240, 320, SDL_WINDOW_SHOWN);
    renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    rgbSurface = IMG_Load("mountain.jpg");
    r.x = 120,r.y=110,r.w=800,r.h=500;
    texture=SDL_CreateTextureFromSurface(renderer2,rgbSurface);
    //end

//    const char * romfile="TETRIS";
//    chip8->LoadROM(romfile);
//    int videoPitch = sizeof(chip8->video[0]) * chip8->VIDEO_WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit)
    {

//       quit = platform.ProcessInput(chip8->keypad);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.key.keysym.sym==SDLK_AC_BACK) quit=true;
            if(event.tfinger.type==SDL_FINGERDOWN) {
                SDL_DestroyRenderer(renderer2);
                SDL_DestroyWindow(window2);

                launchgame(1);
                while (SDL_PollEvent(&event)) ;
                window2 = SDL_CreateWindow("2nd window", 0, display_mode.h+50, 240, 320, SDL_WINDOW_SHOWN);
                renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

                texture=SDL_CreateTextureFromSurface(renderer2,rgbSurface);

            }
        }


//        auto currentTime = std::chrono::high_resolution_clock::now();
//        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();
//
//        if (dt > cycleDelay)
//        {
//            lastCycleTime = currentTime;
//
//            chip8->Cycle();
//
//            platform.Update(chip8->video, videoPitch);
//        }

        SDL_RenderClear(renderer2);
//        texture=SDL_CreateTextureFromSurface(renderer2,rgbSurface);
        SDL_RenderCopy(renderer2,texture, nullptr, &r);
        SDL_RenderPresent(renderer2);

    }

    SDL_FreeSurface(rgbSurface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer2);
    SDL_DestroyWindow(window2);

    SDL_Quit();

    return EXIT_SUCCESS;

}*/

int launchgame(int i)
{
    SDL_DisplayMode display_mode = {0};
    SDL_DisplayMode best_display_mode = {0};
    for (i32 display_mode_num = 0; display_mode_num < SDL_GetNumVideoDisplays(); ++display_mode_num) {
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
    int cycleDelay = 1;
    auto* chip8 = new Chip8();
    auto *platform =new Game("EmuChip8 ", 640, 480, chip8->VIDEO_WIDTH, chip8->VIDEO_HEIGHT);
    const char * romfile="INVADERS";
    chip8->LoadROM(romfile);
    int videoPitch = sizeof(chip8->video[0]) * chip8->VIDEO_WIDTH;
    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;
    SDL_Event event;
    while(!quit){
        quit = platform->ProcessInput(chip8->keypad);
        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (dt > cycleDelay)
        {
            lastCycleTime = currentTime;
            chip8->Cycle();
            platform->Update(chip8->video, videoPitch);
        }

        while (SDL_PollEvent(&event))
        {
            if(event.tfinger.type==SDL_FINGERDOWN)
            {
                SDL_Log("touch x=%lf y=%lf",event.tfinger.x*display_mode.w,event.tfinger.y*display_mode.h);
            }
            if(event.key.keysym.sym==SDLK_AC_BACK) quit=true;
        }


    }
    delete chip8;
    delete platform;
    return EXIT_SUCCESS;
}


int
SDL_main(int argc, __attribute__ ((unused)) char* argv[argc + 1]){

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // TODO(Ryan): Logging
        return EXIT_FAILURE;
    }

    Controller* controller =new Controller();
    controller->Control();

    delete controller;
}