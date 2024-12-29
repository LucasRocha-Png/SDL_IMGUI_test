#pragma once

#include "LTimer.h"
#include "LWindow.h"
#include "LTexture.h"
#include "FPSManager.h"
#include "SDLSubsystemManager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <memory>
#include <string>


class App{
private:
    // Window data
    const std::string& windowTitle;
    int screenWidth;
    int screenHeight;
    
    // Components
    SDLSubsystemManager sdlManager;
    FpsManager fpsManager;
    LWindow windowManager;

    SDL_Event e;
    SDL_Renderer* renderer;

public:
    App(const std::string& windowTitle = "window", int screenWidth = 640, int screenHeight = 480);
    ~App();

    void init();
    bool handleEvent();
    void loop();
};