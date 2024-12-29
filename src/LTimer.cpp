#include "LTimer.h"

LTimer::LTimer(){
    // Initializes variables
    this->startTicks = 0;
    this->pausedTicks = 0;

    this->paused = false;
    this->started = false;
}
LTimer::~LTimer(){}

void LTimer::start(){
    this->started = true;
    this->paused = false;

    //Get the current clock time
    this->startTicks = SDL_GetTicks64();
    this->pausedTicks = 0;
}

void LTimer::stop(){
    this->started = false;
    this->paused = false;
    this->startTicks = 0;
    this->pausedTicks = 0;
}

void LTimer::pause(){
    //If the timer is running and isn't already paused
    if(this->started && !this->paused){
        this->paused = true;

        this->pausedTicks = SDL_GetTicks64() - this->startTicks;
        this->startTicks = 0;
    }
}

void LTimer::unpause(){
    //If the timer is running and paused
    if(this->started && this->paused){
        this->paused = false;
        this->startTicks = SDL_GetTicks64() - this->pausedTicks;
        this->pausedTicks = 0;
    }
}

uint64_t LTimer::getTicks(){
    uint64_t time = 0;
    if(this->started){
        if(this->paused){
            time = this->pausedTicks;
        }
        else{
            time = SDL_GetTicks64() - this->startTicks;
        }
    }
    return time;
}


bool LTimer::isStarted() const{
    return this->started;
}

bool LTimer::isPaused() const{
    return this->paused && this->started;
}