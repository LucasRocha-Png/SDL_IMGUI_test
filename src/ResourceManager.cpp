#include "ResourceManager.h"

ResourceManager::ResourceManager() :
window(nullptr), renderer(nullptr) {}

ResourceManager::~ResourceManager(){
    if (this->window){
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
        SDL_Log("Window destroyed.\n");
    }
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
        SDL_Log("Renderer destroyed.\n");
    }
}

void ResourceManager::init(SDL_Window* window, SDL_Renderer* renderer){
    this->window = window;
    this->renderer = renderer;
}
