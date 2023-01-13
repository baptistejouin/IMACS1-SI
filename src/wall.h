#include <SDL2/SDL.h>

typedef struct Wall
{
	int x1, y1;
	int x2, y2;
} Wall;

typedef struct Walls
{
	Wall wallTop, wallLeft, wallRight, wallBottom;
} Walls;

Walls getAllWalls();
void drawWalls(SDL_Renderer *renderer, Walls *walls);