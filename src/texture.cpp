#include "global.h"
#include "texture.h"
#include <cstdio>


LTexture::LTexture(void) : texture(nullptr), width(0), height(0) {}

int LTexture::get_width(void){
    return this->width;
}

int LTexture::get_height(void){
    return this->height;
}

void LTexture::free(void){
    
    if (this->texture != nullptr){
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
        this->width = 0;
        this->height = 0;
    }
}

LTexture::~LTexture(void){
}



Status LTexture::load_from_file(const char* path){
    this->free();

    // Criamos a superficie
    SDL_Surface* surface = IMG_Load(path);
    if (surface == nullptr){
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return ERR;
    }

    // Criamos um color key para deixar o fundo transparente
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));


    //Criamos a texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if (texture == nullptr){
        SDL_Log("Unable to create the texture %s! SDL Error: %s\n", path, SDL_GetError());
        SDL_FreeSurface(surface);
        return ERR;
    }

    // Liberamos a superficie
    this->width = surface->w;
    this->height = surface->h;
    this->texture = texture;

    SDL_FreeSurface(surface);
    return OK;
}

void LTexture::render(int x, int y, SDL_Rect* clip = nullptr){
    SDL_Rect renderQuad = {x, y, this->width, this->height};

    if(clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(gRenderer, this->texture, clip, &renderQuad);
}