//
// Created by kingpin on 12/11/2021.
//
#include "chip8.h"
//#include <fstream>
#include <android/asset_manager.h>
#include <../SDL/src/core/android/SDL_android.h>
#include "SDL_rwops.h"

#include <SDL.h>
void Chip8::LoadROM(char const* filename) {

    SDL_RWops *ctx = SDL_AllocRW_REAL();
    Android_JNI_FileOpen(ctx,filename,"rb");

    AAsset* asset =(AAsset*) ctx->hidden.androidio.asset;

    if(nullptr==asset) {
        SDL_Log("couldn't load asset %s",filename);
        return;
    }
    long  size = AAsset_getLength(asset);
    char* buffer = new char[size];
    AAsset_read(asset,buffer,size);
    SDL_Log("error : %s",SDL_GetError());
    for (long i = 0; i < size; ++i)
    {
        memory[START_ADDRESS + i] = buffer[i];
    }

    AAsset_close(asset);


}