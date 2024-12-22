#pragma once
#include "global.h"

extern SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
extern SDL_Surface* gCurrentSurface;

SDL_Surface* load_bmp(const char* path);
SDL_Surface* load_png(const char* path);
Status load_media(void);
void free_media(void);