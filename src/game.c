#include <unistd.h>
#include "game.h"
#include "window.h"

void init_grid(int w, int h, int size)
{
    grid = (PointGrid *)malloc(sizeof(PointGrid));
    grid->size = size;
    grid->width = w/grid->size;
    grid->height = h/grid->size;
    grid->gridsize = grid->width * grid->height;
    grid->points = (int *)calloc(grid->gridsize, sizeof(int));
    grid->points[grid->width/2 + (grid->height/2 * grid->width)] = 1;
}

void init_points(int numpoints)
{
    AgPoints_len = numpoints;
    AgPoints = (AgPoint *)calloc(AgPoints_len, sizeof(AgPoint));
    int i;
    for (i = 0; i < AgPoints_len; i++)
    {
        create_point(&AgPoints[i]);
    }
}

void create_point(AgPoint *point)
{
    int corner = rand();
    switch (corner%4)
    {
        case 0:
            point->y = 0;
            point->x = 0;
            break;
        case 1:
            point->y = 0;
            point->x = grid->width-1;
            break;
        case 2:
            point->y = grid->height-1;
            point->x = 0;
            break;
        case 3:
            point->y = grid->height-1;
            point->x = grid->width-1;
            break;
    }
    point->dx = 1.0;
    point->dy = 1.0;
    point->alive = 1;
    point->color = 0xff00ff;
}

void update_point(AgPoint *point)
{
    int cont = rand();
    // Increating multiplier makes points more "erratic"
    if (cont < (RAND_MAX/10)*7)
    {
        int direction = rand();
        if (direction < RAND_MAX/4)
        {
            point->dx = 1;
        }//Accelerate in positive x
        else if (direction < (RAND_MAX/4) * 2)
        {
            point->dy = 1;
        }//Accelerate in positive y
        else if (direction < (RAND_MAX/4) * 3)
        {
            point->dx = -1;
        }//Accelerate in negative x
        else if (direction < RAND_MAX)
        {
            point->dy = -1;
        }//Accelerate in negative y
        else
        {
            printf("Something is really wrong\n");
        }
    }

    if ((point->x + (int)point->dx) < 0 || (point->x + (int)point->dx) > grid->width-1)
    {
        if ((point->x - (int)point->dx) < 1 || (point->x - (int)point->dx) > grid->width-1)
        {
            point->dx *= -1;
            point->x += (int)point->dx;
        }
    }
    else
    {
            point->x += (int)point->dx;
    }

    if ((point->y + (int)point->dy) < 0 || (point->y + (int)point->dy) > grid->height-1)
    {
        if ((point->y - (int)point->dy) < 1 || (point->y - (int)point->dy) > grid->height-1)
        {
            point->dy *= -1;
            point->y += (int)point->dy;
        }
    }
    else
    {
            point->y += (int)point->dy;
    }

    if (point->x < grid->width-1 && grid->points[point->x + (point->y * grid->width) + 1]) 
    {
        settle(point);
    }//Check to right
    else if (point->x >= 0 && grid->points[point->x + (point->y * grid->width) - 1]) 
    {
        settle(point);
    }//Check to left
    else if (point->y > 0 && grid->points[point->x + ((point->y-1) * grid->width)]) 
    {
        settle(point);
    }//Check above
    else if (point->y < grid->height-1 && grid->points[point->x + ((point->y+1) * grid->width)]) 
    {
        settle(point);
    }//Check below
}

void settle(AgPoint *point)
{
    grid->points[point->x + (point->y * grid->width)] = 1;
    point->alive=0;
    //create_point(point);
}

void gameloop(void)
{
    SDL_Surface *surf = SDL_GetWindowSurface(window);
    SDL_Rect rect;
    while (1)
    {
        //usleep(5000);
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
        size_t i;
        for (i = 0; i < AgPoints_len; i++)
        {
            if (AgPoints[i].alive)
            {
                update_point(&AgPoints[i]);
                rect.x = AgPoints[i].x * grid->size;
                rect.y = AgPoints[i].y * grid->size;
                rect.w = grid->size;
                rect.h = grid->size;
                SDL_FillRect(surf,
                             &rect,
                             AgPoints[i].color);
            }
        }
        
        size_t x, y;
        for (y = 0; y < grid->height; y++)
        {
            for (x = 0; x < grid->width; x++)
            {
                if (grid->points[x + (y * grid->width)])
                {
                    rect.x = x * grid->size;
                    rect.y = y * grid->size;
                    rect.w = grid->size;
                    rect.h = grid->size;
                    SDL_FillRect(surf,
                                 &rect,
                                 0x0000ff);
                }
            }
        }
        SDL_UpdateWindowSurface(window);
    }
}
