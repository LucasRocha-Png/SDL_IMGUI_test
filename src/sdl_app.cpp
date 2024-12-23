#include "global.h"
#include "sdl_app.h"
#include "event_handler.h"
#include "texture.h"    

SDL_Renderer* gRenderer = nullptr;
SDL_Window* gWindow = nullptr;

LTexture gArrowTexture;
double degrees = 0.0;
SDL_RendererFlip flipType = SDL_FLIP_NONE;


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
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == nullptr){
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return ERR;
    }

    return OK;
}

Status load_media(void){
    
    if (gArrowTexture.load_from_file("assets/images/arrow.png") == ERR){
        return ERR;
    }

    return OK;
}

/*
    Roda o loop principal do programa
*/
void run_app(void){
    if (load_media() == ERR){
        SDL_Log("Failed to load media. Exiting...\n");
        return;
    }

    bool running = true;
    while (running) {
        if (event_handler() == STOP){
            running = false;
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gArrowTexture.render((SCREEN_WIDTH - gArrowTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gArrowTexture.getHeight() ) / 2, nullptr, degrees, nullptr, flipType);
    
        SDL_RenderPresent(gRenderer);
    }
}

/*
    Libera a mémoria dos objetos SDL
*/
void close_sdl(void){
    gArrowTexture.free();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    IMG_Quit();
	SDL_Quit();
}

