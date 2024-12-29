#pragma once

#include "LTimer.h"


class FpsManager{
    private:
    int maxFps;
    double fps;
    uint64_t countedFrames;

    // Timers
    LTimer fpsTimer; 
    LTimer capTimer; 

    public:
    FpsManager(int maxFps = -1);
    ~FpsManager();
    void startFpsTimer();
    void startFrame();
    void endFrame();  
    double getFps() const;
};