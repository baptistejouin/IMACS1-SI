#include <SDL2/SDL.h>

typedef struct Wall
{
	int x1, y1;
	int x2, y2;
} Wall;

typedef struct Shape
{
	Wall wallTop, wallLeft, wallRight, wallBottom;
} Shape;

Shape getCustomWalls();
Shape getWindowWalls();

void drawShape(SDL_Renderer *renderer, Shape *shape);