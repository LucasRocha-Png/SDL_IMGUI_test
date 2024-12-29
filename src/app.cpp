#include "app.h"

App::App(const std::string& windowTitle, int screenWidth, int screenHeight) : 
windowTitle(windowTitle), screenWidth(screenWidth), screenHeight(screenHeight), renderer(nullptr){}

App::~App(){}

void App::init(){
    this->sdlManager.init();
    this->windowManager.init(this->windowTitle, this->screenWidth, this->screenHeight);
    this->renderer = this->windowManager.createRenderer();
    SDL_Log("SDL initialized successfully.\n");
}

bool App::handleEvent(){
    while(SDL_PollEvent(&this->e)) {
        if (e.type == SDL_QUIT) {   
            return true;
        }
        this->windowManager.handleEvent(this->e);
    } 
    return false;
}

void App::loop(){
    bool isRunning = true;
    this->fpsManager.startFpsTimer();
    while(isRunning){
        if (this->handleEvent() == true) isRunning = false;
        this->fpsManager.startFrame();

        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderClear(this->renderer);
        
        SDL_RenderPresent(this->renderer);
        this->fpsManager.endFrame();
    }
}