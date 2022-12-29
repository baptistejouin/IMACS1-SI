#include <SDL2/SDL.h>

typedef struct Ellipse_Color
{
	Uint8 r, g, b, a;
} Ellipse_Color;

typedef struct Ellipse_Coordinates
{
	int x, y;
} Ellipse_Coordinates;

Ellipse_Color getRandomColor();
SDL_Rect drawEllipseRGBA(SDL_Renderer *renderer);
