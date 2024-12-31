#pragma once

#include "LTimer.h"
#include "LWindow.h"
#include "LTexture.h"
#include "FPSManager.h"
#include "SDLSubsystemManager.h"
#include "ImguiSubsystemManager.h"

#include <memory>
#include <string>


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class App{
private:
    // Window data
    const std::string& windowTitle;
    int screenWidth;
    int screenHeight;
    
    // Components
    SDLSubsystemManager sdlManager;
    ImguiSubsystemManager imguiManager;
    
    LWindow windowManager;

    SDL_Event e;
    SDL_Renderer* renderer;
    SDL_Window* window;

    float xBar;
    float yBar;
    bool isPressed;

public:
    App(const std::string& windowTitle = "window", int screenWidth = 640, int screenHeight = 480);
    ~App();

    void init();
    bool handleEvent();
    void loop();
};