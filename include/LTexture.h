#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <stdexcept> 

class LTexture{
    private:
    SDL_Renderer* renderer;
    SDL_Texture* texture; 
    int width;
    int height;

    public:
    LTexture(SDL_Renderer* renderer);
    ~LTexture();
    int getWidth(void) const;
    int getHeight(void) const;
    

    void loadFromRenderedText(TTF_Font* font, const std::string& textureText, SDL_Color textColor);
    void loadFromFile(const std::string& path);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void free(void);
};
