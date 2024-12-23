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
        else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    //Increase red
                    case SDLK_q:
                    r += 32;
                    break;
                    
                    //Increase green
                    case SDLK_w:
                    g += 32;
                    break;
                    
                    //Increase blue
                    case SDLK_e:
                    b += 32;
                    break;
                    
                    //Decrease red
                    case SDLK_a:
                    r -= 32;
                    break;
                    
                    //Decrease green
                    case SDLK_s:
                    g -= 32;
                    break;
                    
                    //Decrease blue
                    case SDLK_d:
                    b -= 32;
                    break;
                }
            }
    }
    return CONTINUE;
}
