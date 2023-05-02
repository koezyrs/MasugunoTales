#include <iostream>
#include "src/Game.h"

Game* game = nullptr;

int main(int argc, char* args[]){
    //if(argc < 2) return 0;
    //if(strcmp(args[1],"-1sak1")) return 0;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    while(1)
    {
        switch(game->session)
        {
        case INIT:
            game->init(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
        case LOAD_RESOURCES:
            game->loadResources();
            break;
        case LOAD_MIX:
            game->loadMix();
            break;
        case LOAD_DATA:
            game->loadData();
            break;
        case LOGIN:
            game->loginProcess();
            break;
        case REGISTER:
            game->registProcess();
            break;
        case RUNNING:
            frameStart = SDL_GetTicks();

            game->handleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - frameStart;
            if(frameDelay > frameTime){
                SDL_Delay(frameDelay - frameTime);
            }
            break;
        case SAVE_DATA:
            game->saveData();
            break;
        case CLEAR:
            game->clean();
            return 1;
        }
    }
    return 1;
}
