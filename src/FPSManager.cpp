#include "FpsManager.h"
#include <cstdio>


FpsManager::FpsManager(int maxFps) :
maxFps(maxFps), fps(0.0), countedFrames(0){}


void FpsManager::startFpsTimer(){
    this->fpsTimer.start();
}

void FpsManager::setMaxFps(int maxFps){
    this->maxFps = maxFps;
}

void FpsManager::startFrame(){
    this->capTimer.start();
}

void FpsManager::endFrame(){
    if (this->maxFps > 0){
        int frameTicks = capTimer.getTicks();
        int millisecondsPerFrame = 1000 / this->maxFps;
        if (frameTicks < millisecondsPerFrame) SDL_Delay(millisecondsPerFrame - frameTicks);
    }

    this->countedFrames++;
    this->fps = this->countedFrames / (this->fpsTimer.getTicks() / 1000.f);
}

double FpsManager::getFps() const {return this->fps;}