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

        //Handle button events
        for(int i = 0; i < TOTAL_BUTTONS; ++i){
            gButtons[i].handleEvent(&e);
        }
    }
    return CONTINUE;
}
