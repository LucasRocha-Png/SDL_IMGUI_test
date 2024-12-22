#include "sdl_app.h"
#include "event_handler.h"
#include "global.h"
#include "texture.h"    


SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Renderer* gRenderer = nullptr;

/*
    Cria a janela do SDL
*/
Status init_sdl(void){
    // Init SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return ERR;
	}

    // Init IMG_SDL
    int imgFlags = IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        SDL_Log("SDL Image could not initialize! SDL_Error: %s\n", IMG_GetError());
        return ERR;
    }
	
    // Create Window
    gWindow = SDL_CreateWindow("Lucas Rocha", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == nullptr){
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return ERR;
    }

    // Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == nullptr){
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
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

    while (running) {
        if (event_handler() == STOP){
            running = false;
        }

        //Clear screen
        SDL_RenderClear(gRenderer);

        //Render texture to screen
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}


/*
    Libera a mémoria dos objetos SDL
*/
void close_sdl(void){
    free_media();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

	SDL_Quit();
    IMG_Quit();
}

