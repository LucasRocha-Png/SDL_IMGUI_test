#include "app.h"

App::App(const std::string& windowName, int screenWidth, int screenHeight, int maxFps) : 
windowName(windowName), screenWidth(screenWidth), screenHeight(screenHeight), dot(nullptr),
fpsManager(maxFps){
}

App::~App(){
    if (this->window) SDL_DestroyWindow(this->window);
    if (this->renderer) SDL_DestroyRenderer(this->renderer);
    SDL_Log("Exiting.");
}

void App::createWindowAndRenderer(){
    this->window = SDL_CreateWindow(this->windowName.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, SDL_WINDOW_SHOWN);  
    if(this->window == nullptr){
        throw std::runtime_error(std::string("Window could not be created! SDL Error: ") + std::string(SDL_GetError()));
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED); 
    if(this->renderer == nullptr){
        throw std::runtime_error(std::string("Renderer could not be created! SDL Error: ") + std::string(SDL_GetError()));
    }
}

void App::init(){
    this->sdlManager.init();
    this->createWindowAndRenderer();
    this->dot = std::unique_ptr<Dot>(new Dot(this->renderer, this->screenWidth, this->screenHeight));

    SDL_Log("SDL initialized successfully.\n");
}

void App::loadMedia(){
    this->font = TTF_OpenFont("assets/fonts/lazy.ttf", 12);
    if(this->font == nullptr){
        throw std::runtime_error(std::string("Failed to load lazy font! SDL_ttf Error: ") + std::string(TTF_GetError()));
    }


    SDL_Log("Media loaded successfully.\n");
}

bool App::handleEvent(){
    while(SDL_PollEvent(&this->e)) {
        if (e.type == SDL_QUIT) {
            return true;
        }

        dot->handleEvent(this->e);

    } 
    return false;
}

void App::loop(){

    //Set the wall
    SDL_Rect wall;
    wall.x = 300;
    wall.y = 40;
    wall.w = 40;
    wall.h = 400;


    LTexture fpsText(this->renderer);
    SDL_Color textColor = {0, 0, 0, 255};
    bool isRunning = true;

    this->fpsManager.startFpsTimer();
    while(isRunning){
        this->fpsManager.startFrame();
        
        if (this->handleEvent() == true){
            isRunning = false;
        }
      
        dot->move(wall);

        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderClear(this->renderer);

        fpsText.loadFromRenderedText(this->font, (std::string("FPS: ") + std::to_string(this->fpsManager.getFps())).c_str(), textColor); 
        fpsText.render((this->screenWidth - fpsText.getWidth()*1.1), (fpsText.getHeight()*1.1));

        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255 );   
        SDL_RenderDrawRect(this->renderer, &wall);
        
        dot->render();

        SDL_RenderPresent(this->renderer);
        this->fpsManager.endFrame();
    }
}
