#pragma once

#include <cstdio>
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class ImguiSubsystemManager {
private:
    bool isInitialized;
    ImGuiIO* io;

public:
    ImguiSubsystemManager();
    ~ImguiSubsystemManager();
    ImGuiIO* getIO() const;
    void init(SDL_Window* window, SDL_Renderer* renderer);
    void quit();

};
