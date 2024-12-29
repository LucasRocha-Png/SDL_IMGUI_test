#include "Dot.h"

Dot::Dot(SDL_Renderer* renderer, int xLimit, int yLimit) : dotTexture(renderer), xLimit(xLimit), yLimit(yLimit){
    this->dotTexture.loadFromFile("assets/images/dot.bmp");    

    //Initialize the offsets
    this->mPosX = 0;
    this->mPosY = 0;

    // Collision box
    this->collisionBox.w = DOT_WIDTH;
    this->collisionBox.h = DOT_HEIGHT;

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


void Dot::move(SDL_Rect& wall){
    //Move the dot left or right
    this->mPosX += this->mVelX;
    this->collisionBox.x = this->mPosX;

    //If the dot went too far to the left or right
    if((this->mPosX < 0) || ( this->mPosX + this->DOT_WIDTH > this->xLimit) || checkCollision(wall)){
        //Move back
        this->mPosX -= this->mVelX; 
        this->collisionBox.x = this->mPosX;
    }

      //Move the dot up or down
    this->mPosY += this->mVelY;
    this->collisionBox.y = this->mPosY;

    //If the dot went too far up or down
    if( (this->mPosY < 0) || (this->mPosY + this->DOT_HEIGHT > this->yLimit) || checkCollision(wall)){
        //Move back
        this->mPosY -= this->mVelY;
        this->collisionBox.y = this->mPosY;
    }

}

void Dot::render(){
    //Show the dot
    this->dotTexture.render(this->mPosX, this->mPosY);
}

bool Dot::checkCollision(SDL_Rect& wall){
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = wall.x;
    rightA = wall.x + wall.w;
    topA = wall.y;
    bottomA = wall.y + wall.h;

    //Calculate the sides of rect B
    leftB = this->collisionBox.x;
    rightB = this->collisionBox.x + this->collisionBox.w;
    topB = this->collisionBox.y;
    bottomB = this->collisionBox.y + this->collisionBox.h;

    //If any of the sides from A are outside of B
    if(bottomA <= topB){
        return false;
    }

    if(topA >= bottomB){
        return false;
    }

    if(rightA <= leftB){
        return false;
    }

    if(leftA >= rightB){
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}