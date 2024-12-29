#pragma once

#include "LTimer.h"

class FpsManager{
    private:
    int maxFps;
    double fps;
    LTimer fpsTimer; 
    LTimer capTimer; 
    uint64_t countedFrames;


    public:
    FpsManager(int maxFps);
    void startFpsTimer();
    void setMaxFps(int maxFps);
    void startFrame();
    void endFrame();  
    double getFps() const;
};