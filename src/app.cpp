#include "app.h"

App::App(const std::string& windowName, int screenWidth, int screenHeight, int levelWidth, int levelHeight, int maxFps) : 
windowName(windowName), screenWidth(screenWidth), screenHeight(screenHeight), levelWidth(levelWidth), levelHeight(levelHeight), dot(nullptr), fpsManager(maxFps)
{}

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
    this->dot = std::unique_ptr<Dot>(new Dot(this->renderer, this->levelWidth, this->levelHeight));

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
    wall.w = 40;
    wall.h = 400;
    wall.x = (this->levelWidth - wall.w)/2;
    wall.y = (this->levelHeight - wall.h)/2;


    LTexture bgTexture(this->renderer);
    bgTexture.loadFromFile("assets/images/bg.png");


    SDL_Rect camera = {0, 0, this->screenWidth, this->screenHeight};

    LTexture fpsText(this->renderer);
    LTexture ballPosText(this->renderer);
    LTexture wallPosText(this->renderer);

    SDL_Color textColor = {0, 0, 0, 255};

    bool isRunning = true;
    this->fpsManager.startFpsTimer();
    while(isRunning){
        if (this->handleEvent() == true) isRunning = false;
    
        this->fpsManager.startFrame();
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderClear(this->renderer);

        camera.x = (dot->getPosX() + Dot::DOT_WIDTH / 2) - (this->screenWidth / 2);
        camera.y = (dot->getPosY() + Dot::DOT_HEIGHT / 2) - (this->screenHeight / 2);
        if(camera.x < 0) camera.x = 0;
        if(camera.y < 0) camera.y = 0;
        if(camera.x > this->levelWidth - camera.w) camera.x = this->levelWidth - camera.w;
        if(camera.y > this->levelHeight - camera.h) camera.y = this->levelHeight - camera.h;
        
        
        bgTexture.render(0, 0, &camera);

        wall.x = (this->levelWidth - wall.w)/2 - camera.x;
        wall.y = (this->levelHeight - wall.h)/2 - camera.y;
        dot->move(wall);

        SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255); 
        SDL_RenderFillRect(this->renderer, &wall);
        
        dot->render(camera.x, camera.y);
        //Render informations -------------------------------------------
        ballPosText.loadFromRenderedText(this->font, (std::string("Ball X: ") + std::to_string(this->dot->getPosX())).c_str(), textColor);
        ballPosText.render(10, (ballPosText.getHeight()*1.1));

        wallPosText.loadFromRenderedText(this->font, (std::string("Wall X: ") + std::to_string(wall.x)).c_str(), textColor);
        wallPosText.render((ballPosText.getWidth()*1.5), (ballPosText.getHeight()*1.1));

        ballPosText.loadFromRenderedText(this->font, (std::string("Ball Y: ") + std::to_string(this->dot->getPosY())).c_str(), textColor);
        ballPosText.render(10, (ballPosText.getHeight()*2.2));

        wallPosText.loadFromRenderedText(this->font, (std::string("Wall Y: ") + std::to_string(wall.y)).c_str(), textColor);
        wallPosText.render((ballPosText.getWidth()*1.5), (ballPosText.getHeight()*2.2));


        fpsText.loadFromRenderedText(this->font, (std::string("FPS: ") + std::to_string(this->fpsManager.getFps())).c_str(), textColor); 
        fpsText.render((this->screenWidth - fpsText.getWidth()*1.1), (fpsText.getHeight()*1.1));
        SDL_RenderPresent(this->renderer);
        this->fpsManager.endFrame();
    }
}
