#include "game.h"
#define SIZE 10

void init_grid(int w, int h)
{
    grid = (int *)calloc(w*h, sizeof(int));
}

void init_points(int numpoints)
{
    AgPoints = (AgPoint *)calloc(numpoints, sizeof(AgPoint));
    create_points(numpoints);
}

void create_points(int numpoints)
{
    int i;
    for (i = 0; i < numpoints; i++)
    {
        AgPoints[i].alive = 1;
        AgPoints[i].dx = 4.0;
        AgPoints[i].dy = 4.0;
        AgPoint point=AgPoints[i];
        printf("dx: %d, dy: %d, x: %d, y: %d, alive: %d\n", (int)point.dx, (int)point.dy, point.x, point.y, point.alive);
    }
}

void update_point(AgPoint *point)
{
    printf("dx: %f, dy: %f\n", point->dx, point->dy);
    double rx = (double)(rand() % 10 - 5) / 10;
    double ry = (double)(rand() % 10 - 5) / 10;
    printf("rx: %f, ry: %f\n", rx, ry);
    point->dx *= rx;
    point->dy *= ry;
    //point->dx *= (double)(rand() % 3 - 1);
    //point->dy *= (double)(rand() % 3 - 1);
    printf("dx: %f, dy: %f\n", point->dx, point->dy);
    if ((point->x += (int)point->dx) > 0 && (point->x += (int)point->dx) < width)
    {
        point->x += (int)point->dx;
    }
    if ((point->y += (int)point->dy) > 0 && (point->y += (int)point->dy) < height)
    {
        point->y += (int)point->dy;
    }
    printf("x: %d, y: %d\n", point->x, point->y);
}

void gameloop(void)
{
    int length;
    SDL_Surface *surf = SDL_GetWindowSurface(window);
    SDL_Rect rect;
    while (1)
    {
        sleep(1);
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
        }
        SDL_FillRect(surf,
                     NULL,
                     0x000000);
        for (length = sizeof(AgPoints)/sizeof(AgPoints[0]); length >=0; length--)
        {
            //printf("notyo\n");
            if (AgPoints[length].alive)
            {
                printf("yo\n");
                update_point(&AgPoints[length]);
                rect.x = AgPoints[length].x * SIZE;
                rect.y = AgPoints[length].y * SIZE;
                rect.w = SIZE;
                rect.h = SIZE;
                SDL_FillRect(surf,
                             &rect,
                             0xff00ff);
                             
            }
        }
        SDL_UpdateWindowSurface(window);
    }
}

