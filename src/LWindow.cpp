#include "LWindow.h"

LWindow::LWindow(){
    this->window = nullptr;
    this->mouseFocus = false;
    this->keyboardFocus = false;
    this->fullScreen = false;
    this->minimized = false;
    this->width = 0;
    this->height = 0;
}
LWindow::~LWindow(){
    if (this->window) SDL_DestroyWindow(this->window);    
    if (this->renderer) SDL_DestroyRenderer(this->renderer);
}

void LWindow::init(const std::string& windowTitle, int screenWidth, int screenHeight){
    //Create window
    this->window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (this->window == nullptr){
        throw std::runtime_error(std::string("Could not create the window. SDL Error: ") + std::string(SDL_GetError()));
    }

    this->windowTitle = windowTitle;
    this->mouseFocus = true;
    this->keyboardFocus = true;
    this->width = screenWidth;
    this->height = screenHeight;
}

SDL_Renderer* LWindow::createRenderer(){
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr){
        throw std::runtime_error(std::string("Could not create a renderer. SDL_Error: ") + std::string(SDL_GetError()));
    }
    
    return this->renderer;
}

void LWindow::handleEvent(SDL_Event& e){
    //Window event occured
    if(e.type == SDL_WINDOWEVENT){
        //Caption update flag
        bool updateCaption = false;
        switch(e.window.event){
            //Get new dimensions and repaint on window size change
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            this->width = e.window.data1;
            this->height = e.window.data2;
            SDL_RenderPresent(this->renderer);
            break;

            //Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(this->renderer);
            break;

             //Mouse entered window
            case SDL_WINDOWEVENT_ENTER:
            this->mouseFocus = true;
            updateCaption = true;
            break;
            
            //Mouse left window
            case SDL_WINDOWEVENT_LEAVE:
            this->mouseFocus = false;
            updateCaption = true;
            break;

            //Window has keyboard focus
            case SDL_WINDOWEVENT_FOCUS_GAINED:
            this->keyboardFocus = true;
            updateCaption = true;
            break;

            //Window lost keyboard focus
            case SDL_WINDOWEVENT_FOCUS_LOST:
            this->keyboardFocus = false;
            updateCaption = true;
            break;

            //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
            this->minimized = true;
            break;

            //Window maximized
            case SDL_WINDOWEVENT_MAXIMIZED:
            this->minimized = false;
            break;
            
            //Window restored
            case SDL_WINDOWEVENT_RESTORED:
            this->minimized = false;
            break;
        }

        //Update window caption with new data
        if(updateCaption){
            this->changeWindowTitle();
        }
    }

    //Enter exit full screen on return key
    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11){
        if(this->fullScreen){
            SDL_SetWindowFullscreen(this->window, 0);
            this->fullScreen = false;
        }
        else{
            SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            this->fullScreen = true;
            this->minimized = false;
        }
    }
}

void LWindow::changeWindowTitle(){
    std::stringstream caption;
    caption << this->windowTitle << " - MouseFocus: " << ((this->mouseFocus) ? "On" : "Off" ) << 
    " - KeyboardFocus: " << ((this->keyboardFocus) ? "On" : "Off");
    SDL_SetWindowTitle(this->window, caption.str().c_str());
}


int LWindow::getWidth() const{
    return this->width;
}

int LWindow::getHeight() const{
    return this->height;
}

bool LWindow::hasMouseFocus() const{
    return this->mouseFocus;
}

bool LWindow::hasKeyboardFocus() const{
    return this->keyboardFocus;
}

bool LWindow::isMinimized() const{
    return this->minimized;
}