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
            if(e.key.keysym.sym == SDLK_w){
                //Cap if over 255
                if( a + 32 > 255 ){
                    a = 255;
                }
                //Increment otherwise
                else{
                    a += 32;
                }
            }
            //Decrease alpha on s
            else if(e.key.keysym.sym == SDLK_s){
                //Cap if below 0
                if( a - 32 < 0 ){
                    a = 0;
                }
                //Decrement otherwise
                else{
                    a -= 32;
                }
            }
        }
    }
    return CONTINUE;
}
