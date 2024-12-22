#include "texture.h"
#include "global.h"

SDL_Texture* gTexture = nullptr;

SDL_Texture* load_texture(const char* path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if(loadedSurface == nullptr){
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return nullptr;
    }

    //Create texture from surface pixels
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(newTexture == nullptr){
        SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    return newTexture;
}

Status load_media(void){
    //Load PNG texture
    gTexture = load_texture("assets/images/texture.png");
    if(gTexture == nullptr) return ERR;

    return OK;
}

void free_media(void){
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;
}