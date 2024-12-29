#include "SDLSubsystemManager.h"

SDLSubsystemManager::SDLSubsystemManager() : isInitialized(false){}

SDLSubsystemManager::~SDLSubsystemManager(){
    this->quit();
}

void SDLSubsystemManager::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        SDL_Log("Warning: Linear texture filtering not enabled!");
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        throw std::runtime_error(std::string("IMG_Init Error: ") + IMG_GetError());
    }

    if (TTF_Init() == -1) {
        throw std::runtime_error(std::string("TTF_Init Error: ") + TTF_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        throw std::runtime_error(std::string("Mix_OpenAudio Error: ") + Mix_GetError());
    }

    this->isInitialized = true;
    SDL_Log("SDL subsystems initialized successfully.");
}

void SDLSubsystemManager::quit(){
    if (this->isInitialized){
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        SDL_Log("SDL subsystems cleaned up.");
        this->isInitialized = false;
    }
}
