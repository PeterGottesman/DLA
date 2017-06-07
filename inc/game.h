#ifndef _GAME_H
#define _GAME_H

#include <stdlib.h>
#include "SDL2/SDL.h"
#include "window.h"

typedef struct AgPoint
{
    int x, y;
    double dx, dy;
    int alive;
}AgPoint;

AgPoint *AgPoints;
int *grid;

void init_grid(int w, int h);
void init_points(int numpoints);
void create_points(int numpoints);
void update_point(AgPoint *point);
void gameloop(void);

#endif
