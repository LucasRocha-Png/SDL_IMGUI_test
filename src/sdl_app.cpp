#include "global.h"
#include "sdl_app.h"
#include "event_handler.h"
#include "texture.h"    

SDL_Renderer* gRenderer = nullptr;
SDL_Window* gWindow = nullptr;

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;

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
    
    //Load Foo' texture
    if(gSpriteSheetTexture.load_from_file("assets/images/foo_animated.png") == ERR){
        return ERR;
    }

    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w =  64;
    gSpriteClips[ 0 ].h = 205;

    gSpriteClips[ 1 ].x =  64;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w =  64;
    gSpriteClips[ 1 ].h = 205;
    
    gSpriteClips[ 2 ].x = 128;
    gSpriteClips[ 2 ].y =   0;
    gSpriteClips[ 2 ].w =  64;
    gSpriteClips[ 2 ].h = 205;

    gSpriteClips[ 3 ].x = 192;
    gSpriteClips[ 3 ].y =   0;
    gSpriteClips[ 3 ].w =  64;
    gSpriteClips[ 3 ].h = 205;

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

    int frame = 0;
    bool running = true;
    while (running) {
        if (event_handler() == STOP){
            running = false;
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
        gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
        //Go to next frame
        ++frame;

        //Cycle animation
        if(frame / 4 >= WALKING_ANIMATION_FRAMES){
            frame = 0;
        }
    
        SDL_RenderPresent(gRenderer);
    }
}

/*
    Libera a mémoria dos objetos SDL
*/
void close_sdl(void){
    gSpriteSheetTexture.free();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    IMG_Quit();
	SDL_Quit();
}

