#pragma once

#include "global.h"

class LTexture{
    private:
    SDL_Texture* texture; 
    int width;
    int height;

    public:
    LTexture(void);
    ~LTexture(void);
    int getWidth(void);
    int getHeight(void);
    

    #if defined(SDL_TTF_MAJOR_VERSION)
    Status loadFromRenderedText(const char* textureText, SDL_Color textColor);
    #endif
    Status loadFromFile(const char* path);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void free(void);
};
