#include "event_handler.h"
#include "button.h"
#include "global.h"

SDL_Event e;

Status event_handler(void){
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            SDL_Log("Sair do programa.\n");
            return STOP; 
        }        

        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
            startTime = SDL_GetTicks();
        }

    }
    return CONTINUE;
}
