#include "SDL2/SDL.h"
#include "window.h"
#include "game.h"

#define NUMPOINTS 100000
#define SIZE 1

int main(void)
{
    uint32_t subsystems = SDL_INIT_VIDEO;
    if (SDL_Init(subsystems) != 0)
    {
        SDL_Log("Could not init SDL: %s", SDL_GetError());
        return 1;
    }

    if (CreateWindow() != 0)
    {
        return 1;
    }    

    init_grid(WIDTH, HEIGHT, SIZE);
    init_points(NUMPOINTS);
    gameloop();

    SDL_DestroyWindow(window);

    atexit(SDL_Quit);
    return 0;
}
