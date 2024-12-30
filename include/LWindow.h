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

    //Handles window events
    void handleEvent(SDL_Event& e);

    //Focus
    void focus();

    //Window dimensions
    int getWidth() const;
    int getHeight() const;

    //Window focii
    bool hasMouseFocus() const;
    bool hasKeyboardFocus() const;
    bool isMinimized() const;

    // Render
    void render();
    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;

    void changeWindowTitle();

private:
    //Window data
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::string windowTitle;
    unsigned int windowID;

    //Window dimensions
    int width;
    int height;

    //Window focus
    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;
    bool shown;
};