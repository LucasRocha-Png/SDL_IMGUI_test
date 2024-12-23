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

        if(e.type == SDL_KEYDOWN){
            switch( e.key.keysym.sym ){
                case SDLK_a:
                degrees -= 6;
                break;
                
                case SDLK_d:
                degrees += 6;
                break;

                case SDLK_q:
                flipType = SDL_FLIP_HORIZONTAL;
                break;

                case SDLK_w:
                flipType = SDL_FLIP_NONE;
                break;

                case SDLK_e:
                flipType = SDL_FLIP_VERTICAL;
                break;
            }
        }
    }
    return CONTINUE;
}
