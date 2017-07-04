#ifndef _WINDOW_H
#define _WINDOW_H

#include <string.h>
#include "SDL2/SDL.h"

#define WIDTH 640
#define HEIGHT 480

char* title;

SDL_Window *window;
SDL_Renderer *renderer;


int CreateWindow(void);

#endif
