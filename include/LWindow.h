#pragma once

#include <SDL.h>
#include <string>
#include <stdexcept>
#include <sstream>

class LWindow{
public:
    //Intializes internals
    LWindow();
    ~LWindow();

    //Creates window
    void init(const std::string& windowTitle, int screenWidth, int screenHeight);

    //Creates renderer from internal window
    SDL_Renderer* createRenderer();

    //Handles window events
    void handleEvent(SDL_Event& e);

    //Deallocates internals
    void free();

    //Window dimensions
    int getWidth() const;
    int getHeight() const;

    //Window focii
    bool hasMouseFocus() const;
    bool hasKeyboardFocus() const;
    bool isMinimized() const;

    void changeWindowTitle();

private:
    //Window data
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::string windowTitle;
    
    //Window dimensions
    int width;
    int height;

    //Window focus
    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;
};