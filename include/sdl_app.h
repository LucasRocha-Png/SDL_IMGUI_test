#pragma once

#include "global.h"

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface; 

Status init_sdl(void);
void run_app(void);
void close_sdl(void);   