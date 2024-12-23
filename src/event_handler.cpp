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

        if(e.type == SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                //Play high sound effect
                case SDLK_1:
                Mix_PlayChannel( -1, gHigh, 0 );
                break;
                
                //Play medium sound effect
                case SDLK_2:
                Mix_PlayChannel( -1, gMedium, 0 );
                break;
                
                //Play low sound effect
                case SDLK_3:
                Mix_PlayChannel( -1, gLow, 0 );
                break;
                
                //Play scratch sound effect
                case SDLK_4:
                Mix_PlayChannel( -1, gScratch, 0 );
                break;

                case SDLK_9:
                //If there is no music playing
                if( Mix_PlayingMusic() == 0 ){
                    Mix_PlayMusic( gMusic, -1 );
                    break;
                }

                //If the music is paused
                if(Mix_PausedMusic() == 1){
                    //Resume the music
                    Mix_ResumeMusic();
                }
                //If the music is playing
                else{
                    //Pause the music
                    Mix_PauseMusic();
                }
                break;
                
                case SDLK_0:
                //Stop the music
                Mix_HaltMusic();
                break;
            }
        }

    }
    return CONTINUE;
}
