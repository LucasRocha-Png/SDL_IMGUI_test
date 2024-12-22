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
    void render(int x, int y);
    void free(void);
};