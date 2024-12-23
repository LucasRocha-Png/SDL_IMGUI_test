#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface; 
extern SDL_Renderer* gRenderer;

extern TTF_Font* gFont;

extern Mix_Chunk* gScratch;
extern Mix_Chunk* gHigh;
extern Mix_Chunk* gMedium;
extern Mix_Chunk* gLow;

extern Mix_Music* gMusic;

typedef enum{
    ERR,
    OK,
    STOP,
    CONTINUE
} Status;

typedef enum{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
} KeyPressSurfaces;


typedef enum{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
} LButtonSprite;