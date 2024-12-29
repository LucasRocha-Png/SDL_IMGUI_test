#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class ResourceManager{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    ResourceManager();
    ~ResourceManager();
    void init(SDL_Window* window, SDL_Renderer* renderer);
};