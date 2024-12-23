#include "global.h"
#include "sdl_app.h"
#include "event_handler.h"
#include "texture.h"    
#include "button.h"

SDL_Renderer* gRenderer = nullptr;
SDL_Window* gWindow = nullptr;

LTexture gPromptTexture;

//The music that will be played
Mix_Music* gMusic = nullptr;

TTF_Font* gFont;

//The sound effects that will be used
Mix_Chunk* gScratch = nullptr;
Mix_Chunk* gHigh = nullptr;
Mix_Chunk* gMedium = nullptr;
Mix_Chunk* gLow = nullptr;


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

    //Initialize SDL_mixer
    if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0){
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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
    //Load prompt texture
    if(!gPromptTexture.loadFromFile( "assets/images/prompt.png")){
        return ERR;
    }

    //Load music
    gMusic = Mix_LoadMUS( "assets/audio/beat.wav" );
    if(gMusic == nullptr){
        SDL_Log( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return ERR;
    }
    
    //Load sound effects
    gScratch = Mix_LoadWAV( "assets/audio/scratch.wav" );
    if(gScratch == nullptr){
        SDL_Log("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return ERR;
    }
    
    gHigh = Mix_LoadWAV( "assets/audio/high.wav" );
    if(gHigh == nullptr){
        SDL_Log("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return ERR;
    }

    gMedium = Mix_LoadWAV( "assets/audio/medium.wav" );
    if(gMedium == nullptr){
        SDL_Log("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return ERR;
    }

    gLow = Mix_LoadWAV( "assets/audio/low.wav" );
    if(gLow == nullptr){
        SDL_Log("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
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

        gPromptTexture.render(0, 0);
    
        SDL_RenderPresent(gRenderer);
    }
}

/*
    Libera a mémoria dos objetos SDL
*/
void close_sdl(void){
    //Free loaded images
    gPromptTexture.free();

    //Free the sound effects
    Mix_FreeChunk(gScratch);
    Mix_FreeChunk(gHigh);
    Mix_FreeChunk(gMedium);
    Mix_FreeChunk(gLow);
    gScratch = nullptr;
    gHigh = nullptr;
    gMedium = nullptr;
    gLow = nullptr;
    
    //Free the music
    Mix_FreeMusic(gMusic);
    gMusic = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    IMG_Quit();
    TTF_Quit();
    Mix_Quit(); 
	SDL_Quit();
}

