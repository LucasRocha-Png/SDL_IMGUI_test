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
    int get_width(void);
    int get_height(void);
    

    Status load_from_file(const char* path);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect* clip = nullptr);
    void free(void);
};