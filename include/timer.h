#pragma once

#include "global.h"


class LTimer{
    private:
    Uint64 startTicks; // Stores ticks when timer starts
    Uint64 pausedTicks; //Stores ticks when timer was paused

    bool paused; 
    bool started;

    public:
    LTimer();

    bool isPaused();
    bool isStarted();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint64 getTicks();
};


extern LTimer timer;