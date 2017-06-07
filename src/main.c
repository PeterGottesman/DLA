#include "SDL2/SDL.h"
#include "window.h"
#include "game.h"

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

    init_grid(64, 48);
    init_points(1);
    gameloop();

    SDL_DestroyWindow(window);

    atexit(SDL_Quit);
    return 0;
}
