#include "global.h"
#include "sdl_app.h"
#include "event_handler.h"
#include "texture.h"    
#include "button.h"

SDL_Renderer* gRenderer = nullptr;
SDL_Window* gWindow = nullptr;

TTF_Font* gFont;

std::unique_ptr<LButton[]> gButtons (new LButton[TOTAL_BUTTONS]);
std::unique_ptr<SDL_Rect[]> gSpriteClips(new SDL_Rect[BUTTON_SPRITE_TOTAL]);
LTexture gButtonSpriteSheetTexture;

/*
    Cria a janela do SDL
*/
Status init_sdl(void){
    // Init SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return ERR;
	}

    //Set texture filtering to linear
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
		SDL_Log("Warning: Linear texture filtering not enabled!");
        return ERR;
	}

    // Init IMG_SDL
    int imgFlags = IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        SDL_Log("SDL Image could not initialize! SDL_Error: %s\n", IMG_GetError());
        return ERR;
    }

    // Init TTF
    if(TTF_Init() == -1){
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
	//Load sprites
	if(!gButtonSpriteSheetTexture.loadFromFile("assets/images/button.png")){
		return ERR;
	}

    //Set sprites
    for(int i = 0; i < BUTTON_SPRITE_TOTAL; ++i){
        gSpriteClips[ i ].x = 0;
        gSpriteClips[ i ].y = i * 200;
        gSpriteClips[ i ].w = BUTTON_WIDTH;
        gSpriteClips[ i ].h = BUTTON_HEIGHT;
    }

    for(int i = 0; i < TOTAL_BUTTONS; ++i){
        gButtons[i].setSpriteClip(gSpriteClips.get());
        gButtons[i].setSpriteSheet(&gButtonSpriteSheetTexture);
    }

    //Set buttons in corners
    gButtons[ 0 ].setPosition( 0, 0 );
    gButtons[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
    gButtons[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
    gButtons[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );

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

        for(int i = 0; i < TOTAL_BUTTONS; ++i){
            gButtons[i].render();
        }
    
        SDL_RenderPresent(gRenderer);
    }
}

/*
    Libera a mémoria dos objetos SDL
*/
void close_sdl(void){

    gButtonSpriteSheetTexture.free();
    
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    IMG_Quit();
    TTF_Quit();
	SDL_Quit();
}

