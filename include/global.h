#pragma once
#include <SDL.h>
#include <SDL_image.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface; 
extern SDL_Texture* gTexture;
extern SDL_Renderer* gRenderer;
    
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