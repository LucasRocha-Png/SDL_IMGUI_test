#include "main.h"
#include "app.h"

const std::string WINDOW_NAME = "Lucas Rocha";

const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 1280; 
const int LEVEL_HEIGHT = 960;

const int MAX_FPS = 30;

int main(int argc, char* args[]){
    (void)argc;
    (void)args;

    App app(WINDOW_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT, MAX_FPS);
    app.init();
    app.loadMedia();
    app.loop();

	return 0;
}
