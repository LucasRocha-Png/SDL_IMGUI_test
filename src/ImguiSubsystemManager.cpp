#include "ImguiSubsystemManager.h"

ImguiSubsystemManager::ImguiSubsystemManager() : isInitialized(false){}

ImguiSubsystemManager::~ImguiSubsystemManager(){
    this->quit();
}

void ImguiSubsystemManager::init(SDL_Window* window, SDL_Renderer* renderer){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->io = &ImGui::GetIO();
    //(void)this->io;
    this->io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
    this->io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;     
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
    
    this->isInitialized = true;
    printf("ImGui initialized.\n");
}

void ImguiSubsystemManager::quit(){
    if (this->isInitialized){
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        printf("ImGui destroyed.\n");
        this->isInitialized = false;
    }
}

ImGuiIO* ImguiSubsystemManager::getIO() const{
    return this->io;
}
