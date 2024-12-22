#include "sdl_app.h"
#include "event_handler.h"
#include "global.h"
#include "texture.h"    


SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;


/*
    Cria a janela do SDL
*/
Status init_sdl(void){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return ERR;
	}


    int imgFlags = IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        SDL_Log("SDL Image could not initialize! SDL_Error: %s\n", IMG_GetError());
        return ERR;
    }
	
    gWindow = SDL_CreateWindow("Lucas Rocha", 
                                SDL_WINDOWPOS_UNDEFINED, // X
                                SDL_WINDOWPOS_UNDEFINED, // Y
                                SCREEN_WIDTH,            // Width
                                SCREEN_HEIGHT,           // Heigh
                                SDL_WINDOW_SHOWN);
    if(gWindow == nullptr){
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return ERR;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return OK;
}


/*
    Roda o loop principal do programa
*/
void run_app(void){
    bool running = true;

    if (load_media() == ERR){
        running = false;
    }

    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    while (running) {
        if (event_handler() == STOP){
            running = false;
        }

        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);

        SDL_UpdateWindowSurface(gWindow);
    }
}


/*
    Libera a mémoria dos objetos SDL
*/
void close_sdl(void){
    free_media();
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
	SDL_Quit();
}

