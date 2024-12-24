#include "event_handler.h"
#include "timer.h"
#include "global.h"

SDL_Event e;

Status event_handler(void){
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            SDL_Log("Sair do programa.\n");
            return STOP; 
        }        

        if(e.type == SDL_KEYDOWN){
            //Start/stop
            if(e.key.keysym.sym == SDLK_s){
                if(timer.isStarted()){
                    timer.stop();
                }
                else{
                    timer.start();
                }
            }
        
            else if(e.key.keysym.sym == SDLK_p){
                if(timer.isPaused()){
                    timer.unpause();
                }
                else{
                    timer.pause();
                }
            }
        }

    }
    return CONTINUE;
}
