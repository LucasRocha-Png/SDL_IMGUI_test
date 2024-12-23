#pragma once

#include "global.h"
#include "texture.h"

extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;
extern const int TOTAL_BUTTONS;

class LButton{
    private:
    SDL_Point position;
    LButtonSprite currentSprite; // This type is an enum
    LTexture* spriteSheet;
    SDL_Rect* spriteClip;

    public:
    LButton();
    void setSpriteSheet(LTexture* sprite);
    void setSpriteClip(SDL_Rect* clip);
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void render();
};

extern std::unique_ptr<LButton[]> gButtons;