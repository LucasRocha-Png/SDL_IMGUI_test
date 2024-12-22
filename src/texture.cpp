#include "texture.h"
#include "global.h"

#include <cstdio>


SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = nullptr;

SDL_Surface* load_bmp(const char* path){
    SDL_Surface* LoadedSurface = SDL_LoadBMP(path);
    if(LoadedSurface == nullptr){
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    return LoadedSurface;
}

Status load_media(void){
    //Default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = load_bmp("assets/images/press.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) return ERR;

    //Up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = load_bmp("assets/images/up.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) return ERR;

    //Down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = load_bmp("assets/images/down.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr) return ERR;

    //Left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = load_bmp("assets/images/left.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) return ERR;

    //Right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = load_bmp("assets/images/right.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) return ERR;

    return OK;
}

void free_media(void){
    for (int i=KEY_PRESS_SURFACE_DEFAULT; i<KEY_PRESS_SURFACE_TOTAL; i++){
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = nullptr;
    }
}