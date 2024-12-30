#include "app.h"

App::App(const std::string& windowTitle, int screenWidth, int screenHeight) : 
windowTitle(windowTitle), screenWidth(screenWidth), screenHeight(screenHeight), renderer(nullptr), window(nullptr){

}

App::~App(){
    SDL_Log("App destroyed.");
}

void App::init(){
    this->sdlManager.init();
    this->windowManager.init(this->windowTitle, this->screenWidth, this->screenHeight);
    this->window = this->windowManager.getWindow();
    this->renderer = this->windowManager.getRenderer();
    SDL_Log("App initialized.");
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
    int angle = 0;
    LTexture texture(this->renderer);
    texture.createBlank(this->screenWidth, this->screenHeight, SDL_TEXTUREACCESS_TARGET);
    SDL_Point screenCenter = {this->screenWidth / 2, this->screenHeight / 2};
    this->fpsManager.startFpsTimer();
    while(isRunning){
        if (this->handleEvent() == true) isRunning = false;
        this->fpsManager.startFrame();

        if (this->screenHeight != this->windowManager.getHeight() || this->screenWidth != this->windowManager.getWidth()){
            this->screenHeight = this->windowManager.getHeight();
            this->screenWidth = this->windowManager.getWidth();
            texture.createBlank(this->screenWidth, this->screenHeight, SDL_TEXTUREACCESS_TARGET);
            screenCenter.x = this->screenWidth/2;
            screenCenter.y = this->screenHeight/2;
        }

        angle = (angle > 360) ? 0 : angle+2;

        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderClear(this->renderer);
        texture.setAsRenderTarget();
        SDL_RenderClear(this->renderer);

        //Render red filled quad
        SDL_Rect fillRect = { this->screenWidth / 4, this->screenHeight / 4, this->screenWidth / 2, this->screenHeight / 2 };
        SDL_SetRenderDrawColor( this->renderer, 0xFF, 0x00, 0x00, 0xFF );        
        SDL_RenderFillRect( this->renderer, &fillRect );

        //Render green outlined quad
        SDL_Rect outlineRect = { this->screenWidth / 6, this->screenHeight / 6, this->screenWidth * 2 / 3, this->screenHeight * 2 / 3 };
        SDL_SetRenderDrawColor( this->renderer, 0x00, 0xFF, 0x00, 0xFF );        
        SDL_RenderDrawRect( this->renderer, &outlineRect );
        
        //Draw blue horizontal line
        SDL_SetRenderDrawColor( this->renderer, 0x00, 0x00, 0xFF, 0xFF );        
        SDL_RenderDrawLine( this->renderer, 0, this->screenHeight / 2, this->screenWidth, this->screenHeight / 2 );

        //Draw vertical line of yellow dots
        SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0x00, 0xFF );
        for( int i = 0; i < this->screenHeight; i += 4 ){
            SDL_RenderDrawPoint( this->renderer, this->screenWidth / 2, i );
        }

        texture.resetRenderTarget();
        
        texture.render(0, 0, nullptr, angle, &screenCenter);

        SDL_RenderPresent(this->renderer);
        this->fpsManager.endFrame();
    }
}