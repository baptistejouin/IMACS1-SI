#include <SDL2/SDL.h>

typedef struct Ellipse_Color
{
	Uint8 r, g, b, a;
} Ellipse_Color;

typedef struct Ellipse_Coordinates
{
	int x, y;
} Ellipse_Coordinates;
typedef struct Ellipse_Direction
{
	int vx, vy;
} Ellipse_Direction;

typedef struct Ellipse
{
	int rad;
	bool visible;
	Ellipse_Coordinates coordinates;
	Ellipse_Direction direction;
	Ellipse_Color color;
} Ellipse;

// Générer une couleur RGBA aléatoire, avec un alpha fixe
Ellipse_Color getRandomColor();

// Générer un position aléatoire à partir de la hauteur et de la largeur d'un plan
Ellipse_Coordinates getRandomCoordinates(Shape *shape);

Ellipse_Direction getRandomDirectionVector(int maxVect);

// Générer des ellipses en RGBA
Ellipse getEllipseRGBA(Shape *shape);

// Dessiner des ellipses données dans un renderer donné
void drawEllipses(SDL_Renderer *renderer, Ellipse ellipse[]);

// Mise à jour des coordonées des ellipses suivant leurs direction et leurs position
void moveEllipes(Ellipse ellipse[], Shape *shape);

// Gestion du click sur une ellise
void handleOnClick(Ellipse ellipse[], int mouseX, int mouseY);