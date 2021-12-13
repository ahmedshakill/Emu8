//
// Created by kingpin on 12/13/2021.
//

#include "menu.h"
#include <SDL_image.h>
Menu::Menu(const char *title, int windowWidth, int windowHeight):windowWidth(windowWidth),windowHeight(windowHeight) {
    window = SDL_CreateWindow("Menu", 0, 0, 240, 320, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    rgbSurface = IMG_Load("GameListMenu.jpg");
    r.x = 0,r.y=0,r.w=1124,r.h=2048;
    texture=SDL_CreateTextureFromSurface(renderer,rgbSurface);

    halfHeight=windowHeight/2;
    halfWidth=windowWidth/2;

}

Menu::~Menu() {
    // Destroy all at end

    SDL_FreeSurface(rgbSurface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Menu::ClearEvents(){
    while (SDL_PollEvent(&event)) ;
}

void Menu::RecreateWindowAndRenderer()
{
    window = SDL_CreateWindow("Menu", 0, 0, 240, 320, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    texture=SDL_CreateTextureFromSurface(renderer,rgbSurface);
}
void Menu::DestroyWindowAndRenderer()
{
    // to show another window

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
}
void Menu::Update() {
    while (!gameSelected and !quit)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,texture, nullptr, &r);
        SDL_RenderPresent(renderer);
//        ProcessInput();
        while (SDL_PollEvent(&event))
        {
            if(event.key.keysym.sym==SDLK_AC_BACK) quit=true;
            if(event.tfinger.type==SDL_FINGERDOWN) {

                selectionNo=12;
                SDL_Log("touch x=%lf y=%lf",event.tfinger.x*windowWidth,event.tfinger.y*windowHeight);

                int xpos=event.tfinger.x*windowWidth;
                int ypos=event.tfinger.y*windowHeight;

                if(xpos<halfWidth){

                    if(ypos<200 && ypos>0){
                        //Blinky
                        selectionNo=0;
                    }
                    else if(ypos<370 &&  ypos>280){
                        //missile
                        selectionNo= 1;
                         }
                    else if(ypos<560 &&  ypos>460){
                        //pong2
                        selectionNo= 2;
                    }
                    else if(ypos<750 &&  ypos>640){
                        //syzygy
                        selectionNo= 3;
                    }
                    else if(ypos<930 &&  ypos>830 ){
                        //blitz
                        selectionNo= 4;
                    }
                    else if(ypos<1100 && ypos>1020 ){
                        //connect4
                        selectionNo= 5;
                    }
                    else if(ypos<1280 && ypos>1180){
                        //Invaders
                        selectionNo= 6;
                    }
                    else if(ypos<1460 && ypos>1361){
                        //maze
                        selectionNo= 7;
                    }
                    else if(ypos<1640 && ypos>1560){
                        //tetris
                        selectionNo= 8;
                    }
                    else if(ypos<1830 && ypos>1760){
                        //ufo
                        selectionNo= 9;
                    }
                    else if(ypos<2030 && ypos>1910){
                        //vers
                        selectionNo= 10;
                    }
                    else if(ypos<2230 && ypos>2110){
                        //vers
                        selectionNo= 11;
                    }

                }
                else if(xpos>halfWidth)
                {
                    if(ypos<200 && ypos>0){
                        //Blinky
                        selectionNo=12;
                    }
                    else if(ypos<370 &&  ypos>280){
                        //missile
                        selectionNo= 13;
                    }
                    else if(ypos<560 &&  ypos>460){
                        //pong2
                        selectionNo= 14;
                    }
                    else if(ypos<750 &&  ypos>640){
                        //syzygy
                        selectionNo= 15;
                    }
                    else if(ypos<930 &&  ypos>830 ){
                        //blitz
                        selectionNo= 16;
                    }
                    else if(ypos<1100 && ypos>1020 ){
                        //connect4
                        selectionNo= 17;
                    }
                    else if(ypos<1280 && ypos>1180){
                        //Invaders
                        selectionNo= 18;
                    }
                    else if(ypos<1460 && ypos>1361){
                        //maze
                        selectionNo= 19;
                    }
                    else if(ypos<1640 && ypos>1560){
                        //tetris
                        selectionNo= 20;
                    }
                    else if(ypos<1830 && ypos>1760){
                        //ufo
                        selectionNo= 21;
                    }
                    else if(ypos<2030 && ypos>1910){
                        //vers
                        selectionNo= 22;
                    }

                }

                gameSelected=true;

            }
        }
    }
    gameSelected=false;
}


int Menu::getSelectedRom() {
    Update();
    ClearEvents();
//    SDL_RenderClear(renderer);
//    SDL_RenderPresent(renderer);
//    DestroyWindowAndRenderer();
    return selectionNo;
}















bool Menu::ProcessInput() {
    while (SDL_PollEvent(&event))
    {
        if(event.key.keysym.sym==SDLK_AC_BACK) quit=true;
        if(event.tfinger.type==SDL_FINGERDOWN) {
//            DestroyWindowAndRenderer();
            //launchgame(1);
            gameSelected=true;

            selectionNo=7;
//            ClearEvents();
//            RecreateWindowAndRenderer();

        }
    }
}
