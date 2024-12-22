#include "main.h"
#include "global.h"
#include "sdl_app.h"


const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[]){
    SDL_Log("Iniciando programa.\n");

    if (init_sdl() == ERR){
        SDL_Log("Failed to initialize!\n");
        return -1;
    }

	run_app();
    
    close_sdl();

	return 0;
}
