#include <SDL2/SDL.h>

typedef struct Ellipse_Color
{
	Uint8 r, g, b, a;
} Ellipse_Color;

typedef struct Ellipse_Coordinates
{
	int x, y;
} Ellipse_Coordinates;

// Générer une couleur RGBA aléatoire, avec un alpha fixe
Ellipse_Color getRandomColor();

// Générer un position aléatoire à partir de la hauteur et de la largeur d'un plan
Ellipse_Coordinates getRandomCoordinates(int width, int height);

SDL_Rect drawEllipseRGBA(SDL_Renderer *renderer);
