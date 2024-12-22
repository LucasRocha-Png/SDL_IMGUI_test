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

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(gRenderer);

        //Render red filled quad
        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);        
        SDL_RenderFillRect(gRenderer, &fillRect);

        //Render green outlined quad
        SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );        
        SDL_RenderDrawRect( gRenderer, &outlineRect );

        //Draw blue horizontal line
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
        SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

        //Draw vertical line of yellow dots
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
        for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
        {
            SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
        }

        //Update screen
        SDL_RenderPresent( gRenderer );
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

