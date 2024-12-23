#include "global.h"
#include "button.h"
#include "texture.h"

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

LButton::LButton(){
    this->position.x = 0;
    this->position.y = 0;
    this->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
    this->spriteSheet = nullptr;
    this->spriteClip = nullptr;
}

void LButton::setPosition(int x, int y){
    this->position.x = x;
    this->position.y = y;
}

void LButton::setSpriteClip(SDL_Rect* clip){
    this->spriteClip = clip;
}

void LButton::setSpriteSheet(LTexture* sprite){
    this->spriteSheet = sprite;
}

void LButton::handleEvent(SDL_Event* e){
    //If mouse event happened
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < this->position.x){
            inside = false;
        }
        //Mouse is right of the button
        else if(x > this->position.x + BUTTON_WIDTH){
            inside = false;
        }
        //Mouse above the button
        else if(y < this->position.y){
            inside = false;
        }
        //Mouse below the button
        else if(y > this->position.y + BUTTON_HEIGHT){
            inside = false;
        }

        //Mouse is outside button
        if(!inside){
            this->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else{
            //Set mouse over sprite
            switch(e->type){
                case SDL_MOUSEMOTION:
                this->currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            
                case SDL_MOUSEBUTTONDOWN:
                this->currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
                
                case SDL_MOUSEBUTTONUP:
                this->currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

void LButton::render(){
    //Show current button sprite
    this->spriteSheet->render(this->position.x, this->position.y, &spriteClip[this->currentSprite]);
}