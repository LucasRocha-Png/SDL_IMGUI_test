#include <SDL2/SDL.h>
#include "../include/main.h"

#include <stdio.h>

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* gWindow = nullptr; //Window
SDL_Surface* gScreenSurface = nullptr; //The surface
SDL_Surface* gHelloWorld = nullptr; //The image

bool init(void){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
	}
	
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(gWindow == nullptr){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

int load(void){
    gHelloWorld = SDL_LoadBMP( "data/hello_world.bmp" );
    if( gHelloWorld == nullptr){
        printf( "Unable to load image %s! SDL Error: %s\n", "data/hello_world.bmp", SDL_GetError() );
        return false;
    }

    return true;
}

void exit_event(void){
    SDL_Event e; 
    bool quit = false; 
    while(quit == false){ 
        while(SDL_PollEvent(&e)){ 
            if(e.type == SDL_QUIT) quit = true; 
        } 
    }
}


void close(void){
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

	SDL_Quit();
}


int main(int argc, char* args[]){
    printf("Iniciando programa.\n");


    if (!init()){
        printf("Failed to initialize!\n");
        return -1;
    }

    if (!load()){
        printf("Failed to load the image!\n");
        return -1;
    }
	
    SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
    SDL_UpdateWindowSurface(gWindow);
    
    exit_event();
    close();

	return 0;
}
