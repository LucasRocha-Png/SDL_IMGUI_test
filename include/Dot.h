#pragma once
#include "LTexture.h"

class Dot{
    private:
        //The X and Y offsets of the dot
        int posX, posY;
        int velX, velY;
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

        int getPosX() const;
        int getPosY() const;

        //Takes key presses and adjusts the dot's velocity
        void handleEvent(SDL_Event& e);

        //Moves the dot
        void move(SDL_Rect& wall);

        // Check Collision
        bool checkCollision(SDL_Rect& a, SDL_Rect& b);

        //Shows the dot on the screen
        void render(int camX, int camY);
};