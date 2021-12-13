//
// Created by kingpin on 12/11/2021.
//

#include "game.h"
#include <SDL_image.h>

Game::Game(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight): windowWidth(windowWidth), windowHeight(windowHeight)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    texture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
    SDL_SetTextureColorMod(texture,255,0,0);

    keypadSurface=IMG_Load("keypad.png");
    keypadTexture=SDL_CreateTextureFromSurface(renderer,keypadSurface);
    keypadRect={0,1030,1024,1030};
    gameRect={0,0,1024,1024};
}

Game::~Game()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
//    SDL_Quit();
}

void Game::Update(void const* buffer, int pitch)
{
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, &gameRect);
    SDL_RenderCopy(renderer, keypadTexture, nullptr, &keypadRect);
    SDL_RenderPresent(renderer);
}

bool Game::ProcessInput(uint8_t* keys)
{
    bool quit = false;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if(event.key.keysym.sym==SDLK_AC_BACK)
        {
            quit=true;
            SDL_Log("backbutton clicked");
        }
        if(event.tfinger.type==SDL_FINGERDOWN)
        {
            SDL_Log("touch x=%lf y=%lf",event.tfinger.x*windowWidth,event.tfinger.y*windowHeight);
             xpos=event.tfinger.x*windowWidth;
             ypos=event.tfinger.y*windowHeight;

            if(xpos<220 and xpos>50){
                if(ypos<1340 and ypos>1160){
                    keys[1] = 1;
                }
                if(ypos<1650 and ypos>1450){
                    keys[4] = 1;
                }
                if(ypos<1950 and ypos>1750){
                    keys[7] = 1;
                }
                if(ypos<2234 and ypos>2024){
                    keys[0xA] = 1;
                }
            }
            if(xpos<490 and xpos>290){
                if(ypos<1340 and ypos>1160){
                    keys[2] = 1;
                }
                if(ypos<1650 and ypos>1450){
                    keys[5] = 1;
                }
                if(ypos<1950 and ypos>1750){
                    keys[8] = 1;
                }
                if(ypos<2234 and ypos>2024){
                    keys[0] = 1;
                }
            }
            if(xpos<750 and xpos>550){
                if(ypos<1340 and ypos>1160){
                    keys[3] = 1;
                }
                if(ypos<1650 and ypos>1450){
                    keys[6] = 1;
                }
                if(ypos<1950 and ypos>1750){
                    keys[9] = 1;
                }
                if(ypos<2234 and ypos>2024){
                    keys[0xB] = 1;
                }
            }
            if(xpos<980 and xpos>820){
                if(ypos<1340 and ypos>1160){
                    keys[0xC] = 1;
                }
                if(ypos<1650 and ypos>1450){
                    keys[0xD] = 1;
                }
                if(ypos<1950 and ypos>1750){
                    keys[0xE] = 1;
                }
                if(ypos<2234 and ypos>2024){
                    keys[0xF] = 1;
                }
            }
        }
        if(event.tfinger.type==SDL_FINGERUP)
        {
            SDL_Log("touch x=%lf y=%lf",event.tfinger.x*windowWidth,event.tfinger.y*windowHeight);
            xpos=event.tfinger.x*windowWidth;
            ypos=event.tfinger.y*windowHeight;

            if(xpos<220 and xpos>50){
                if(ypos<1340 and ypos>1160){
                    keys[1] = 0;
                }
                if(ypos<1650 and ypos>1450){
                    keys[4] = 0;
                }
                if(ypos<1950 and ypos>1750){
                    keys[7] = 0;
                }
                if(ypos<2234 and ypos>2024){
                    keys[0xA] = 0;
                }
            }
            if(xpos<490 and xpos>290){
                if(ypos<1340 and ypos>1160){
                    keys[2] = 0;
                }
                if(ypos<1650 and ypos>1450){
                    keys[5] = 0;
                }
                if(ypos<1950 and ypos>1750){
                    keys[8] = 0;
                }
                if(ypos<2234 and ypos>2024){
                    keys[0] = 0;
                }
            }
            if(xpos<750 and xpos>550){
                if(ypos<1340 and ypos>1160){
                    keys[3] = 0;
                }
                if(ypos<1650 and ypos>1450){
                    keys[6] = 0;
                }
                if(ypos<1950 and ypos>1750){
                    keys[9] = 0;
                }
                if(ypos<2234 and ypos>2024){
                    keys[0xB] = 0;
                }
            }
            if(xpos<980 and xpos>820){
                if(ypos<1340 and ypos>1160){
                    keys[0xC] = 0;
                }
                if(ypos<1650 and ypos>1450){
                    keys[0xD] = 0;
                }
                if(ypos<1950 and ypos>1750){
                    keys[0xE] = 0;
                }
                if(ypos<2234 and ypos>2024){
                    keys[0xF] = 0;
                }
            }
        }
    }

    return quit;
}