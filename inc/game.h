#ifndef _GAME_H
#define _GAME_H

#include <stdlib.h>
#include "SDL2/SDL.h"

typedef struct AgPoint
{
    int16_t x, y;
    double dx, dy;
    int alive;
    int color;
}AgPoint;

typedef struct PointGrid
{
    int width, height;
    int size;
    //For dead points
    int gridsize;
    int *points;
}PointGrid;

size_t AgPoints_len;
AgPoint *AgPoints;
PointGrid *grid;

void init_grid(int w, int h, int size);
void init_points(int numpoints);
void create_point(AgPoint *point);
void update_point(AgPoint *point);
void settle(AgPoint *point);
void gameloop(void);

#endif
