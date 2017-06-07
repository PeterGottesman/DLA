#ifndef _WINDOW_H
#define _WINDOW_H

#include <string.h>
#include "SDL2/SDL.h"

int width;
int height;
char* title;

SDL_Window *window;
SDL_Renderer *renderer;


int CreateWindow(void);

#endif
