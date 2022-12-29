#include <SDL2/SDL.h>

typedef struct Ball
{
	int x, y, r;
	float vx, vy;
	Uint8 red, green, blue, alpha;
} Ball;

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

int getRandomDirectionVector(int min, int max);

// Générer des ellipses en RGBA
Ball getEllipseRGBA();

// Dessiner des ellipses données dans un renderer donné
void drawEllipses(SDL_Renderer *renderer, Ball ellipse[]);

// Mise à jour des coordonées des ellipses suivant leurs direction et leurs position
void moveEllipes(Ball ellipse[], Walls walls);