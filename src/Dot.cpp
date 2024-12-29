#include "Dot.h"

Dot::Dot(SDL_Renderer* renderer, int xLimit, int yLimit) : dotTexture(renderer), xLimit(xLimit), yLimit(yLimit){
    this->dotTexture.loadFromFile("assets/images/dot.bmp");    

    //Initialize the offsets
    this->mPosX = 0;
    this->mPosY = 0;

    //Initialize the velocity
    this->mVelX = 0;
    this->mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e ){
    //If a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //Adjust the velocity
        switch(e.key.keysym.sym){
            case SDLK_UP: this->mVelY -= this->DOT_VEL; break;
            case SDLK_DOWN: this->mVelY += this->DOT_VEL; break;
            case SDLK_LEFT: this->mVelX -= this->DOT_VEL; break;
            case SDLK_RIGHT: this->mVelX += this->DOT_VEL; break;
        }
    }

    //If a key was released
    else if(e.type == SDL_KEYUP && e.key.repeat == 0){
        //Adjust the velocity
        switch(e.key.keysym.sym){
            case SDLK_UP: this->mVelY += this->DOT_VEL; break;
            case SDLK_DOWN: this->mVelY -= this->DOT_VEL; break;
            case SDLK_LEFT: this->mVelX += this->DOT_VEL; break;
            case SDLK_RIGHT: this->mVelX -= this->DOT_VEL; break;
        }
    }
}

void Dot::move(){
    //Move the dot left or right
    this->mPosX += this->mVelX;

    //If the dot went too far to the left or right
    if((this->mPosX < 0) || ( this->mPosX + this->DOT_WIDTH > this->xLimit)){
        //Move back
        this->mPosX -= this->mVelX;
    }

      //Move the dot up or down
    this->mPosY += this->mVelY;

    //If the dot went too far up or down
    if( (this->mPosY < 0) || (this->mPosY + this->DOT_HEIGHT > this->yLimit)){
        //Move back
        this->mPosY -= this->mVelY;
    }
}

void Dot::render(){
    //Show the dot
    this->dotTexture.render(this->mPosX, this->mPosY);
}