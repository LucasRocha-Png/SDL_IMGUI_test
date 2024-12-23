#include "global.h"
#include "texture.h"
#include <cstdio>


LTexture::LTexture(void) : texture(nullptr), width(0), height(0) {}

int LTexture::getWidth(void){
    return this->width;
}

int LTexture::getHeight(void){
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

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect renderQuad = {x, y, this->width, this->height};

    if(clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, this->texture, clip, &renderQuad, angle, center, flip);
}


void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
    SDL_SetTextureColorMod(this->texture, red, green, blue );
}

void LTexture::setBlendMode(SDL_BlendMode blending){
    //Set blending function
    SDL_SetTextureBlendMode(this->texture, blending);
}
        
void LTexture::setAlpha(Uint8 alpha){
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(this->texture, alpha);
}