#include "main.h"
#include "app.h"

const std::string WINDOW_TITLE = "Lucas Rocha";

const int SCREEN_WIDTH = 1280 ; 
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[]){
    (void)argc;
    (void)args;

    App app(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    app.init();
    app.loop();

	return 0;
}
