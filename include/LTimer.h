#pragma once

#include <SDL.h>

class LTimer{
    private:
    uint64_t startTicks; // Stores ticks when timer starts
    uint64_t pausedTicks; //Stores ticks when timer was paused

    bool paused; 
    bool started;

    public:
    LTimer();
    ~LTimer();

    bool isPaused() const;
    bool isStarted() const;

    void start();
    void stop();
    void pause();
    void unpause();

    uint64_t getTicks();
};