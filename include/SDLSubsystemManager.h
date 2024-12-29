#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdexcept>

class SDLSubsystemManager {
private:
    bool isInitialized;

public:
    SDLSubsystemManager();
    ~SDLSubsystemManager();
    void init();
    void quit();

};
