#include "app.h"

App::App(const std::string& windowTitle, int screenWidth, int screenHeight) : 
windowTitle(windowTitle), screenWidth(screenWidth), screenHeight(screenHeight), renderer(nullptr), window(nullptr), isPressed(false){
this->xBar = this->screenWidth/2;
this->yBar = this->screenHeight/2;
}

App::~App(){
    SDL_Log("App destroyed.");
}

void App::init(){
    this->sdlManager.init();
    this->windowManager.init(this->windowTitle, this->screenWidth, this->screenHeight);
    this->window = this->windowManager.getWindow();
    this->renderer = this->windowManager.getRenderer();
    this->imguiManager.init(this->window, this->renderer);
    SDL_Log("App initialized.");
}

bool App::handleEvent(){
    while(SDL_PollEvent(&this->e)) {
        if (e.type == SDL_QUIT) {   
            return true;
        }
        this->windowManager.handleEvent(this->e);
        ImGui_ImplSDL2_ProcessEvent(&this->e);

        if (e.type == SDL_MOUSEBUTTONDOWN && this->imguiManager.getIO()->WantCaptureMouse == false) {
            // Verifica se o botão pressionado ou solto foi o que nos interessa (ex: botão esquerdo)
            if (e.button.button == SDL_BUTTON_LEFT) {
                
                // Se o evento for de pressionar, ativa o estado
                bool isPressed = (e.type == SDL_MOUSEBUTTONDOWN);
                // Se o botão foi pressionado, atualiza as coordenadas do mouse
                if (isPressed) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    this->xBar = static_cast<float>(x);
                    this->yBar = static_cast<float>(y);
                }
            }
        }


        if ((e.type == SDL_MOUSEBUTTONDOWN && this->imguiManager.getIO()->WantCaptureMouse == false) || e.type == SDL_MOUSEBUTTONUP) {
            if (e.button.button == SDL_BUTTON_LEFT) {    
                this->isPressed = (e.type == SDL_MOUSEBUTTONDOWN);
            }
        }

        if (this->isPressed){
            int x, y;
            SDL_GetMouseState(&x, &y);
            this->xBar = static_cast<int>(x);
            this->yBar = static_cast<int>(y);
        }


    }
    return false;
}

void App::loop(){
    LTexture foo(this->renderer);
    foo.createBlank(300, 300);
    float angle = 0.0;
    float minAngle = -360.0f;       // Valor mínimo
    float maxAngle = 360.0f;     // Valor máximo
    float angleVelocity = 0.0;
    int revolutions = 0;
    float backgroundColor[3] = {1.0f, 1.0f, 1.0f};
    while(true){
        if (this->handleEvent() == true) break;
        Uint8 r = static_cast<Uint8>(backgroundColor[0] * 255.0f);
        Uint8 g = static_cast<Uint8>(backgroundColor[1] * 255.0f);
        Uint8 b = static_cast<Uint8>(backgroundColor[2] * 255.0f);
        SDL_SetRenderDrawColor(this->renderer, r, g, b, 255);
        SDL_RenderClear(this->renderer);
        this->screenWidth = this->windowManager.getWidth(); this->screenHeight = this->windowManager.getHeight();
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("FPS: %.2f", this->imguiManager.getIO()->Framerate);
        ImGui::SeparatorText("Cor de Fundo");

        // Calcular a área disponível dentro da janela (ou frame)
        ImVec2 windowSize = ImGui::GetWindowSize();  // Obtém o tamanho da janela ou frame
        ImVec2 contentRegion = ImGui::GetContentRegionAvail(); // Área disponível para widgets
        float xPos = (contentRegion.x - 200) * 0.5f; // 200 é a largura estimada do ColorEdit3
        ImGui::SetCursorPosX(xPos);
        ImGui::ColorPicker3("##CorDeFundo", backgroundColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

        ImGui::SeparatorText("Barra");
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Revoluções: %d", revolutions); ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 0, 0).Value);
        ImGui::PushStyleColor(ImGuiCol_Button, ImColor(r, g, b).Value);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(r-32, g-32, b-32).Value);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImColor(r-32, g-32, b-32).Value);
        xPos = (contentRegion.x - ImGui::CalcTextSize("Reseta").x);
        ImGui::SetCursorPosX(xPos);
        if (ImGui::Button("Reseta")) {
            angle = 0;
            angleVelocity = 0;
            revolutions = 0;
            xBar = this->screenWidth/2;
            yBar = this->screenHeight/2;
        }
        ImGui::PopStyleColor(4);
        ImGui::SetItemTooltip("Reseta as revoluções, o ângulo, a velocidade e a posição da barra.");
        
        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 0, 0).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(r, g, b).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(r-32, g-32, b-32).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive,  ImColor(r-32, g-32, b-32).Value);
        ImGui::DragScalar("##angulo", ImGuiDataType_Float, &angle, 0.01f, &minAngle, &maxAngle, "%.2f");
        ImGui::PopStyleColor(4);
        ImGui::SameLine(); ImGui::Text("Ângulo");

        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 0, 0).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(r, g, b).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(r-32, g-32, b-32).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive,  ImColor(r-32, g-32, b-32).Value);
        ImGui::PushStyleColor(ImGuiCol_SliderGrab,  ImColor(r+32, g+32, b+32).Value);
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,  ImColor(r+64, g+64, b+64).Value);
        ImGui::SliderFloat("##velocidade", &angleVelocity, -32.0f, 32.0f, "%.2f");
        ImGui::PopStyleColor(6);
        ImGui::SameLine(); ImGui::Text("Vel. Angular");
        
        
        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 0, 0).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(r, g, b).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(r-32, g-32, b-32).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive,  ImColor(r-32, g-32, b-32).Value);
        ImGui::PushStyleColor(ImGuiCol_SliderGrab,  ImColor(r+32, g+32, b+32).Value);
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,  ImColor(r+64, g+64, b+64).Value);
        ImGui::SliderFloat("##X", &xBar, 0.0f, static_cast<float>(this->screenWidth), "%.2f");
        ImGui::PopStyleColor(6);
        ImGui::SameLine(); ImGui::Text("X");

        
        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0, 0, 0).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(r, g, b).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(r-32, g-32, b-32).Value);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive,  ImColor(r-32, g-32, b-32).Value);
        ImGui::PushStyleColor(ImGuiCol_SliderGrab,  ImColor(r+32, g+32, b+32).Value);
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,  ImColor(r+64, g+64, b+64).Value);
        ImGui::SliderFloat("##Y", &yBar, static_cast<float>(this->screenHeight), 0.0f, "%.2f");
        ImGui::PopStyleColor(6);
        ImGui::SameLine(); ImGui::Text("Y");

        ImGui::End();

        //ImGui::ShowDemoWindow(nullptr);

        if (angle > maxAngle || angle < minAngle) {
            angle = 0;
            revolutions += 1;
        } else {
            angle += angleVelocity;
        }

        foo.setAsRenderTarget();
        SDL_RenderClear(this->renderer);
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(this->renderer, 0, 150, 300, 150);
        foo.resetAsRenderTarget();
    //    SDL_Point center = { foo.getWidth() / 2, foo.getHeight() / 2 };
        foo.render(xBar-foo.getWidth()/2, yBar-foo.getHeight()/2, nullptr, angle);

        ImGui::Render();
        //SDL_RenderSetScale(this->renderer, this->imguiManager.getIO()->DisplayFramebufferScale.x, this->imguiManager.getIO()->DisplayFramebufferScale.y);    
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), this->renderer);
        SDL_RenderPresent(this->renderer);
    }
}