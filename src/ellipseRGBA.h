#include <SDL2/SDL.h>

typedef struct Ellipse_Color
{
	Uint8 r;
	Uint8 b;
	Uint8 g;
	Uint8 a;
} Ellipse_Color;

Ellipse_Color getRandomColor();
SDL_Rect drawEllipseRGBA(SDL_Renderer *renderer);
