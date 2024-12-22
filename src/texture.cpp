#include "texture.h"
#include "global.h"

SDL_Texture* gTexture = nullptr;

SDL_Texture* load_texture(const char* path)
{
    //Create texture from surface pixels
    SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path);
    if(newTexture == nullptr){
        SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    }

    return newTexture;
}

Status load_media(void){
    //Load PNG texture
    
    return OK;
}

void free_media(void){
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;
}