#pragma once

#include "LTimer.h"
#include "LTexture.h"
#include "FPSManager.h"
#include "SDLSubsystemManager.h"
#include "Dot.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <memory>
#include <string>


class App{
private:
    const std::string& windowName;
    int screenWidth;
    int screenHeight;
    int maxFps;

    SDL_Event e;
    TTF_Font* font;
    SDL_Window* window; 
    SDL_Renderer* renderer;
    std::unique_ptr<Dot> dot;
    
    SDLSubsystemManager sdlManager;
    FpsManager fpsManager;

public:
    App(const std::string& windowName = "window", int screenWidth = 640, int screenHeight = 480, int maxFps = 60);
    ~App();

    void init();
    void createWindowAndRenderer();

    void loadMedia();
    bool handleEvent();
    void loop();
};