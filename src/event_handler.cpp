#include "event_handler.h"
#include "texture.h"
#include "global.h"


SDL_Event e;

Status event_handler(void){
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            SDL_Log("Sair do programa.\n");
            return STOP; 
        }

        if(e.type == SDL_KEYDOWN){ // Se alguma tecla foi precionada
            switch(e.key.keysym.sym){ // Pega o tipo da tecla
                case SDLK_RIGHT:
                    break;

                default:
                    break;
            }
        }
    }
    return CONTINUE;
}
