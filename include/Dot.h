#pragma once
#include "LTexture.h"

class Dot{
    private:
        //The X and Y offsets of the dot
        int mPosX, mPosY;
        int mVelX, mVelY;
        LTexture dotTexture;
        int xLimit, yLimit;

    public:
        //The dimensions of the dot
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;

        //Maximum axis velocity of the dot
        static const int DOT_VEL = 10;

        //Initializes the variables
        Dot(SDL_Renderer* renderer, int xLimit, int yLimit);

        //Takes key presses and adjusts the dot's velocity
        void handleEvent(SDL_Event& e);

        //Moves the dot
        void move();

        //Shows the dot on the screen
        void render();
};