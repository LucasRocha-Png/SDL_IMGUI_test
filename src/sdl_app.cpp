#include "global.h"
#include "sdl_app.h"
#include "event_handler.h"
#include "texture.h"    
#include "timer.h"

SDL_Renderer* gRenderer = nullptr;
SDL_Window* gWindow = nullptr;

LTexture gTimeTextTexture;
LTexture gPausePromptTexture;
LTexture gStartPromptTexture;

LTimer timer;

TTF_Font* gFont;

Uint64 startTime = 0;

std::stringstream timeText;

//Set text color as black
SDL_Color textColor = { 0, 0, 0, 255 };

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
     //Open the font
    gFont = TTF_OpenFont("assets/fonts/lazy.ttf", 28);
    if(gFont == nullptr){
        SDL_Log("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        return ERR;
    }
        
    if(!gStartPromptTexture.loadFromRenderedText("Press S to Start or Stop the Timer", textColor)){
        return ERR;
    }
    
    //Load pause prompt texture
    if(!gPausePromptTexture.loadFromRenderedText("Press P to Pause or Unpause the Timer", textColor)){
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

        //Set text to be rendered
        timeText.str( "" );
        timeText << "Seconds since start time " << (timer.getTicks() / 1000.f) ; 

        //Render text
        if(!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)){
            SDL_Log("Unable to render time texture!\n");
        }


        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gStartPromptTexture.render( ( SCREEN_WIDTH - gStartPromptTexture.getWidth() ) / 2, 0 );
        gPausePromptTexture.render( ( SCREEN_WIDTH - gPausePromptTexture.getWidth() ) / 2, gStartPromptTexture.getHeight() );
        gTimeTextTexture.render( ( SCREEN_WIDTH - gTimeTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTimeTextTexture.getHeight() ) / 2 );

        SDL_RenderPresent(gRenderer);
    }
}

/*
    Libera a mémoria dos objetos SDL
*/
void close_sdl(void){
    gStartPromptTexture.free();
    gPausePromptTexture.free();
    gTimeTextTexture.free();


    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    IMG_Quit();
    TTF_Quit();
    Mix_Quit(); 
	SDL_Quit();
}

