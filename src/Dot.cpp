#include "Dot.h"

Dot::Dot(SDL_Renderer* renderer, int xLimit, int yLimit) : dotTexture(renderer), xLimit(xLimit), yLimit(yLimit){
    this->dotTexture.loadFromFile("assets/images/dot.bmp");    

    //Initialize the offsets
    this->posX = 0;
    this->posY = 0;

    //Initialize the velocity
    this->velX = 0;
    this->velY = 0;
}

int Dot::getPosX() const{
    return this->posX;
}

int Dot::getPosY() const{
    return this->posY;
}

void Dot::handleEvent( SDL_Event& e ){
    //If a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //Adjust the velocity
        switch(e.key.keysym.sym){
            case SDLK_UP: this->velY -= this->DOT_VEL; break;
            case SDLK_DOWN: this->velY += this->DOT_VEL; break;
            case SDLK_LEFT: this->velX -= this->DOT_VEL; break;
            case SDLK_RIGHT: this->velX += this->DOT_VEL; break;
        }
    }

    //If a key was released
    else if(e.type == SDL_KEYUP && e.key.repeat == 0){
        //Adjust the velocity
        switch(e.key.keysym.sym){
            case SDLK_UP: this->velY += this->DOT_VEL; break;
            case SDLK_DOWN: this->velY -= this->DOT_VEL; break;
            case SDLK_LEFT: this->velX += this->DOT_VEL; break;
            case SDLK_RIGHT: this->velX -= this->DOT_VEL; break;
        }
    }
}


void Dot::move(SDL_Rect& wall) {
    SDL_Rect dotRect = {this->posX, this->posY, DOT_WIDTH, DOT_HEIGHT};

    //Move the dot left or right
    this->posX += this->velX;

    //If the dot went too far to the left or right
    if( ( this->posX < 0 ) || (this->posX + DOT_WIDTH > this->xLimit)){
        //Move back
        this->posX -= this->velX;
    }

    //Move the dot up or down
    this->posY += this->velY;

    //If the dot went too far up or down
    if( ( this->posY < 0 ) || ( this->posY + DOT_HEIGHT > this->yLimit) ){
        //Move back
        this->posY -= this->velY;
    }
}


void Dot::render(int camX, int camY){
    //Show the dot relative to the camera
    this->dotTexture.render(this->posX - camX, this->posY - camY);
}

bool Dot::checkCollision(SDL_Rect& a, SDL_Rect& b) {
    return !(a.x + a.w <= b.x || b.x + b.w <= a.x || 
             a.y + a.h <= b.y || b.y + b.h <= a.y);
}
